#include <iostream>

//Matrix as a struct

struct Matrix
{
public:
	int** _matrixValues;
	int* _sizeX = (int*)malloc(sizeof(int));
	int* _sizeY = (int*)malloc(sizeof(int));

	/*
	public:
		Matrix(int y, int x)
		{
			_matrixValues = (int**)calloc(y, sizeof(int*));

			*_sizeY = y;
			*_sizeX = x;

			for (int i = 0; i < *_sizeY; i++)
			{
				_matrixValues[i] = (int*)calloc(x, sizeof(int));

				for (int j = 0; j < *_sizeX; j++)
				{
					std::cout << " Enter matrix value (" << i + 1 << "," << j + 1 << ")\n ";
					int inp;

					std::cin >> inp;

					_matrixValues[i][j] = inp;
				}
			}
			std::cout << "\n";
		}

		void PrintMatrixValues()
		{
			std::cout << " Matrix is\n";

			for (int i = 0; i < *_sizeY; i++)
			{
				std::cout << " ";
				for (int j = 0; j < *_sizeX; j++)
				{
					std::cout << _matrixValues[i][j] << " ";
				}
				std::cout << "\n";
			}

			std::cout << "\n";
		}

		void CountSumOfPosEl()
		{
			std::cout << " ";
			int sum = 0;
			for (int i = 0; i < *_sizeY; i++)
			{
				for (int j = 0; j < *_sizeX; j++)
				{
					if (_matrixValues[i][j] > 0)
					{
						sum += _matrixValues[i][j];
					}
				}
			}
			std::cout << "Sum of positive elements = " << sum << "\n\n";
		}

		void DeleteMatrixContent()
		{
			for (int i = 0; i < *_sizeY; i++)
			{
				free(_matrixValues[i]);
			}

			free(_matrixValues);
			delete(_sizeX);
			delete(_sizeY);
		} */
};

Matrix* CreateMatrix()
{
	std::cout << " Enter size X of matrix\n ";
	int x;
	std::cin >> x;
	std::cout << "\n\n";

	std::cout << " Enter size Y of matrix\n ";
	int y;
	std::cin >> y;
	std::cout << "\n\n";

	Matrix* matrix = new Matrix();
	matrix->_matrixValues = (int**)calloc(y, sizeof(int*));

	*matrix->_sizeY = y;
	*matrix->_sizeX = x;

	for (int i = 0; i < *matrix->_sizeY; i++)
	{
		matrix->_matrixValues[i] = (int*)calloc(*matrix->_sizeX, sizeof(int));
	}

	std::cout << "\n";
	return matrix;
}

Matrix* CreateMatrix(int x, int y)
{
	Matrix* matrix = new Matrix();
	matrix->_matrixValues = (int**)calloc(y, sizeof(int*));

	*matrix->_sizeY = y;
	*matrix->_sizeX = x;

	for (int i = 0; i < *matrix->_sizeY; i++)
	{
		matrix->_matrixValues[i] = (int*)calloc(*matrix->_sizeX, sizeof(int));
	}

	std::cout << "\n";
	return matrix;
}

void SetMatrix(Matrix* matrix)
{
	for (int i = 0; i < *matrix->_sizeY; i++)
	{
		for (int j = 0; j < *matrix->_sizeX; j++)
		{
			std::cout << " Enter matrix value (" << i + 1 << "," << j + 1 << ")\n ";
			int inp;

			std::cin >> inp;

			matrix->_matrixValues[i][j] = inp;
		}
	}
}

void PrintMatrixValues(Matrix* matrix)
{
	std::cout << " Matrix is\n";

	for (int i = 0; i < *matrix->_sizeY; i++)
	{
		std::cout << " ";
		for (int j = 0; j < *matrix->_sizeX; j++)
		{
			std::cout << matrix->_matrixValues[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
}

void CountSumOfPosEl(Matrix* matrix)
{
	std::cout << " ";
	int sum = 0;
	for (int i = 0; i < *matrix->_sizeY; i++)
	{
		for (int j = 0; j < *matrix->_sizeX; j++)
		{
			if (matrix->_matrixValues[i][j] > 0)
			{
				sum += matrix->_matrixValues[i][j];
			}
		}
	}
	std::cout << "Sum of positive elements = " << sum << "\n\n";
}

void DeleteMatrixContent(Matrix* matrix)
{
	for (int i = 0; i < *matrix->_sizeY; i++)
	{
		free(matrix->_matrixValues[i]);
	}

	free(matrix->_matrixValues);
	delete(matrix->_sizeX);
	delete(matrix->_sizeY);
}

void DeleteMatrix(Matrix* matrix)
{
	/*matrix->DeleteMatrixContent();*/
	DeleteMatrixContent(matrix);
	free(matrix);
}

//Matrix as a dynamic array

int* GetSizeOfMatrix(int** matrix)
{
	int* size = (int*)calloc(2, sizeof(int));

	size[0] = _msize(matrix) / sizeof(int*);
	size[1] = _msize(matrix[0]) / sizeof(int);

	return size;
}

int** CreateSimpleMatrix()
{
	std::cout << " Enter size X of matrix\n ";
	int x;
	std::cin >> x;
	std::cout << "\n\n";

	std::cout << " Enter size Y of matrix\n ";
	int y;
	std::cin >> y;
	std::cout << "\n\n";

	int** matrix = (int**)calloc(y, sizeof(int*));

	for (int i = 0; i < y; i++)
	{
		matrix[i] = (int*)calloc(x, sizeof(int));
	}

	std::cout << "\n";
	return matrix;
}

void SetMatrix(int** matrix)
{
	int* size = GetSizeOfMatrix(matrix);
	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 0; j < size[1]; j++)
		{
			std::cout << " Enter matrix value (" << i + 1 << "," << j + 1 << ")\n ";
			int inp;

			std::cin >> inp;

			matrix[i][j] = inp;
		}
	}
}

void PrintMatrixValues(int** matrix)
{
	std::cout << " Matrix is\n";

	int* size = GetSizeOfMatrix(matrix);

	for (int i = 0; i < size[0]; i++)
	{
		std::cout << " ";
		for (int j = 0; j < size[1]; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
}

void CountSumOfPosEl(int** matrix)
{
	int* size = GetSizeOfMatrix(matrix);

	std::cout << " ";
	int sum = 0;
	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 0; j < size[1]; j++)
		{
			if (matrix[i][j] > 0)
			{
				sum += matrix[i][j];
			}
		}
	}
	std::cout << "Sum of positive elements = " << sum << "\n\n";
}

void DeleteMatrix(int** matrix)
{
	int* size = GetSizeOfMatrix(matrix);

	for (int i = 0; i < size[0]; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

int main()
{
	//Prefabricated matrixes
	std::cout << "\n Matrix is 2x2\n -------------\n";
	Matrix* matrix1 = CreateMatrix(2, 2);
	SetMatrix(matrix1);
	PrintMatrixValues(matrix1);
	CountSumOfPosEl(matrix1);

	std::cout << "\n Matrix is 3x1\n -------------\n";
	Matrix* matrix2 = CreateMatrix(1, 3);
	SetMatrix(matrix2);
	PrintMatrixValues(matrix2);
	CountSumOfPosEl(matrix2);

	std::cout << "\n Matrix is 1x5\n -------------\n";
	Matrix* matrix3 = CreateMatrix(5, 1);
	SetMatrix(matrix3);
	PrintMatrixValues(matrix3);
	CountSumOfPosEl(matrix3);

	std::cout << "\n Want to create your own matrix?\n -------------------------------\n";
	while (1)
	{
		/*Matrix* matrix = CreateMatrix();  // Create a struct matrix

		SetMatrix(matrix);
		PrintMatrixValues(matrix);
		CountSumOfPosEl(matrix);
		DeleteMatrix(matrix);*/

		int** matrix = CreateSimpleMatrix();   // Create an array matrix 

		SetMatrix(matrix);
		PrintMatrixValues(matrix);
		CountSumOfPosEl(matrix);
		DeleteMatrix(matrix);
	}
}


//Matrix* CreateMatrix()
//{
//	std::cout << " Enter size X of matrix\n ";
//	int x;
//	std::cin >> x;
//	std::cout << "\n\n";
//
//	std::cout << " Enter size Y of matrix\n ";
//	int y;
//	std::cin >> y;
//	std::cout << "\n\n";
//
//	Matrix* matrix = new Matrix(/*y, x*/);
//	return matrix;
//}

/*class Matrix
{
	int** _matrixValues;
	int* _sizeX = (int*)malloc(sizeof(int));
	int* _sizeY = (int*)malloc(sizeof(int));
public:
	Matrix(int y, int x)
	{
		_matrixValues = (int**)calloc(y, sizeof(int*));

		*_sizeY = y;
		*_sizeX = x;

		for (int i = 0; i < *_sizeY; i++)
		{
			_matrixValues[i] = (int*)calloc(x, sizeof(int));

			for (int j = 0; j < *_sizeX; j++)
			{
				std::cout << " Enter matrix value (" << i + 1 << "," << j + 1 << ")\n ";
				int inp;

				std::cin >> inp;

				_matrixValues[i][j] = inp;
			}
		}
		std::cout << "\n";
	}

	void PrintMatrixValues()
	{
		std::cout << " Matrix is\n";

		for (int i = 0; i < *_sizeY; i++)
		{
			std::cout << " ";
			for (int j = 0; j < *_sizeX; j++)
			{
				std::cout << _matrixValues[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "\n";
	}

	void CountSumOfPosEl()
	{
		std::cout << " ";
		int sum = 0;
		for (int i = 0; i < *_sizeY; i++)
		{
			for (int j = 0; j < *_sizeX; j++)
			{
				if (_matrixValues[i][j] > 0)
				{
					sum += _matrixValues[i][j];
				}
			}
		}
		std::cout << "Sum of positive elements = " << sum << "\n\n";
	}

	void DeleteMatrixContent()
	{
		for (int i = 0; i < *_sizeY; i++)
		{
			free(_matrixValues[i]);
		}

		free(_matrixValues);
		delete(_sizeX);
		delete(_sizeY);
	}
}; */


