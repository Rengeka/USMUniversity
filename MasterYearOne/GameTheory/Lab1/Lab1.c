/*
 * lab1.c
 *
 * Compile:  mpicc -O2 -o lab1 lab1.c
 * Run:      mpirun -np 4 ./lab1
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

#define ROWS 10
#define COLS 10

/* 1 - static matrix with a guaranteed saddle point, 0 - random matrix */
#define USE_STATIC_MATRIX 1

/* Saddle point coordinates in the static matrix (0-based) */
#define SADDLE_ROW 4
#define SADDLE_COL 4
#define SADDLE_VALUE 50

typedef struct
{
    int row_count;
    int column_count;
    int start_row;
    int *data;
} Submatrix;

int*  generate_random_matrix(int rows, int cols);
int*  generate_static_matrix(int rows, int cols);
void  distribute_submatrices(const int *payoff_matrix, Submatrix *submatrix, int process_count, int rank);
void  free_submatrix(Submatrix *submatrix);
int   compute_local_maximin(const Submatrix *submatrix);
int*  compute_local_column_maxima(const Submatrix *submatrix);
int   compute_minimax(const int *global_column_maxima, int total_cols);
void  mark_optimal_rows(const Submatrix *submatrix, int maximin, int *optimal_row_flags);
void  mark_optimal_columns(const int *global_column_maxima, int total_cols, int minimax, int *optimal_column_flags);
void  print_result(int maximin, int minimax, const int *optimal_row_flags, const int *optimal_column_flags);

int main(int argc, char **argv)
{
    int rank, process_count;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    int *payoff_matrix = NULL;
    if (rank == 0)
    {
        srand(42);

#if USE_STATIC_MATRIX
        payoff_matrix = generate_static_matrix(ROWS, COLS);
#else
        payoff_matrix = generate_random_matrix(ROWS, COLS);
#endif
    }

    Submatrix submatrix;
    distribute_submatrices(payoff_matrix, &submatrix, process_count, rank);

    if (rank == 0)
    {
        free(payoff_matrix);
    }

    int local_maximin = compute_local_maximin(&submatrix);

    int maximin;
    MPI_Allreduce(&local_maximin, &maximin, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

    int *local_column_maxima = compute_local_column_maxima(&submatrix);
    int *global_column_maxima = malloc(COLS * sizeof(int));

    MPI_Allreduce(local_column_maxima, global_column_maxima, COLS, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

    int minimax = compute_minimax(global_column_maxima, COLS);

    int *optimal_row_flags = calloc(ROWS, sizeof(int));
    int *optimal_column_flags = calloc(COLS, sizeof(int));

    mark_optimal_rows(&submatrix, maximin, optimal_row_flags);
    mark_optimal_columns(global_column_maxima, COLS, minimax, optimal_column_flags);

    int *global_row_flags = malloc(ROWS * sizeof(int));
    int *global_column_flags = malloc(COLS * sizeof(int));

    MPI_Allreduce(optimal_row_flags, global_row_flags, ROWS, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(optimal_column_flags, global_column_flags, COLS, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0)
    {
        print_result(maximin, minimax, global_row_flags, global_column_flags);
    }

    free_submatrix(&submatrix);
    free(local_column_maxima);
    free(global_column_maxima);
    free(optimal_row_flags);
    free(optimal_column_flags);
    free(global_row_flags);
    free(global_column_flags);

    MPI_Finalize();
    return 0;
}

int* generate_random_matrix(int rows, int cols)
{
    int *matrix = malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i * cols + j] = rand() % 100;
        }
    }

    return matrix;
}

int* generate_static_matrix(int rows, int cols)
{
    int *matrix = malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int value = rand() % 100;

            if (i != SADDLE_ROW)
            {
                value = value % SADDLE_VALUE;
            }

            if (j != SADDLE_COL)
            {
                value = SADDLE_VALUE + 1 + (value % (100 - SADDLE_VALUE - 1));
            }

            if (i == SADDLE_ROW && j != SADDLE_COL)
            {
                value = SADDLE_VALUE + (rand() % 20);
            }

            if (j == SADDLE_COL && i != SADDLE_ROW)
            {
                value = SADDLE_VALUE - (rand() % 20);
            }

            matrix[i * cols + j] = value;
        }
    }

    matrix[SADDLE_ROW * cols + SADDLE_COL] = SADDLE_VALUE;

    return matrix;
}

void distribute_submatrices(const int *payoff_matrix, Submatrix *submatrix, int process_count, int rank)
{
    int rows_per_process = (ROWS + process_count - 1) / process_count;

    int *row_counts    = malloc(process_count * sizeof(int));
    int *start_rows    = malloc(process_count * sizeof(int));
    int *send_counts   = malloc(process_count * sizeof(int));
    int *displacements = malloc(process_count * sizeof(int));

    for (int p = 0; p < process_count; p++)
    {
        int first_row = p * rows_per_process;
        int last_row  = first_row + rows_per_process;

        if (first_row > ROWS) first_row = ROWS;
        if (last_row  > ROWS) last_row  = ROWS;

        int count = last_row - first_row;
        if (count < 0) count = 0;

        row_counts[p]    = count;
        start_rows[p]    = first_row;
        send_counts[p]   = count * COLS;
        displacements[p] = first_row * COLS;
    }

    MPI_Scatter(row_counts, 1, MPI_INT, &submatrix->row_count,  1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(start_rows, 1, MPI_INT, &submatrix->start_row,  1, MPI_INT, 0, MPI_COMM_WORLD);

    submatrix->column_count = COLS;
    submatrix->data         = malloc(submatrix->row_count * COLS * sizeof(int));

    MPI_Scatterv(payoff_matrix, send_counts, displacements, MPI_INT,
                 submatrix->data, submatrix->row_count * COLS, MPI_INT,
                 0, MPI_COMM_WORLD);

    free(row_counts);
    free(start_rows);
    free(send_counts);
    free(displacements);
}

void free_submatrix(Submatrix *submatrix)
{
    free(submatrix->data);
    submatrix->data = NULL;
}

int compute_local_maximin(const Submatrix *submatrix)
{
    int best = INT_MIN;

    for (int i = 0; i < submatrix->row_count; i++)
    {
        int row_minimum = INT_MAX;

        for (int j = 0; j < submatrix->column_count; j++)
        {
            int value = submatrix->data[i * submatrix->column_count + j];
            if (value < row_minimum) row_minimum = value;
        }

        if (row_minimum > best)
        {
            best = row_minimum;
        }
    }

    return best;
}

int* compute_local_column_maxima(const Submatrix *submatrix)
{
    int *column_maxima = malloc(submatrix->column_count * sizeof(int));

    for (int j = 0; j < submatrix->column_count; j++)
    {
        int column_maximum = INT_MIN;

        for (int i = 0; i < submatrix->row_count; i++)
        {
            int value = submatrix->data[i * submatrix->column_count + j];
            if (value > column_maximum) column_maximum = value;
        }

        column_maxima[j] = column_maximum;
    }

    return column_maxima;
}

int compute_minimax(const int *global_column_maxima, int total_cols)
{
    int best = INT_MAX;

    for (int j = 0; j < total_cols; j++)
    {
        if (global_column_maxima[j] < best)
        {
            best = global_column_maxima[j];
        }
    }

    return best;
}

void mark_optimal_rows(const Submatrix *submatrix, int maximin, int *optimal_row_flags)
{
    for (int i = 0; i < submatrix->row_count; i++)
    {
        int row_minimum = INT_MAX;

        for (int j = 0; j < submatrix->column_count; j++)
        {
            int value = submatrix->data[i * submatrix->column_count + j];
            if (value < row_minimum) row_minimum = value;
        }

        if (row_minimum == maximin)
        {
            optimal_row_flags[submatrix->start_row + i] = 1;
        }
    }
}

void mark_optimal_columns(const int *global_column_maxima, int total_cols, int minimax, int *optimal_column_flags)
{
    for (int j = 0; j < total_cols; j++)
    {
        if (global_column_maxima[j] == minimax)
        {
            optimal_column_flags[j] = 1;
        }
    }
}

void print_result(int maximin, int minimax, const int *optimal_row_flags, const int *optimal_column_flags)
{
    printf("=== Rezultat ===\n");
    printf("Valoarea inferioara a jocului (maximin) = %d\n", maximin);
    printf("Valoarea superioara a jocului (minimax) = %d\n", minimax);

    if (maximin != minimax)
    {
        printf("maximin != minimax => nu exista solutii in strategii pure.\n");
        return;
    }

    printf("maximin == minimax => exista solutie.\n");
    printf("Multimea NE = { ");

    int first = 1;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (optimal_row_flags[i] && optimal_column_flags[j])
            {
                printf("%s(%d,%d)", first ? "" : ", ", i + 1, j + 1);
                first = 0;
            }
        }
    }

    printf(" }\n");
}