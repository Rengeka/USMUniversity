#include <iostream>
#include "Matrix.h"
#include <string>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, Matrix<T>& matrix)
{
    for (int i = 0; i < matrix.GetSizeX(); i++) {
        for (int j = 0; j < matrix.GetSizeY(); j++) {
            os << matrix.GetValues()[i][j] << " ";
        }
        os << "\n";
    }

    return os;
}

int main()
{

    /*
    Разработать шаблонный класс Матрица.
    Перегрузить операции + , -. * .
    В классе должен быть конструктор.
    Предусмотреть член - функцию для печати элементов класса.
    */

    int** values1 = new int*[3];

    values1[0] = new int[3] {0, 1, 2};
    values1[1] = new int[3] {3, 4, 5};
    values1[2] = new int[3] {6, 7, 8};

    int** values2 = new int* [3];

    values2[0] = new int[3] {9, 10, 11};
    values2[1] = new int[3] {12, 13, 14};
    values2[2] = new int[3] {15, 16, 17};

    
    Matrix<int> matrix1 = *new Matrix<int>(3, 3, values1);

    Matrix<int> matrix2 = *new Matrix<int>(3, 3, values2);

    (matrix1 + matrix2).PrintMatrix();
    (matrix1 - matrix2).PrintMatrix();
    (matrix1 * matrix2).PrintMatrix();

    cout << matrix1;
    Matrix<int> matrix3( matrix1 + matrix2);
    cout << matrix3;
    cout << (matrix1 + matrix2);
    cout << (matrix1 - matrix2);
    cout << (matrix1 * matrix2);
}
