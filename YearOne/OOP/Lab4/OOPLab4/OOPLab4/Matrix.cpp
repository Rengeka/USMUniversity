#include "Matrix.h"
#include <iostream>

//int Matrix<int>::GetSizeX()
//{
//	return _sizeX;
//}
//
//int Matrix<int>::GetSizeY() 
//{
//	return _sizeY;
//}
//
//int** Matrix<int>::GetValues()
//{
//	return _values;
//}
//
//void Matrix<int>::SetValues(int* values[])
//{
//	_values = values;
//}

//
//using namespace std;
//
//template<typename T>
//Matrix<T>::Matrix(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY)
//{
//    _values = new T * [_sizeX];
//    for (int i = 0; i < _sizeX; ++i)
//    {
//        _values[i] = new T[_sizeY];
//    }
//}
//
//
//template<typename T>
//Matrix<T>::~Matrix()
//{
//    if (_values != nullptr)
//    {
//        for (int i = 0; i < _sizeX; ++i)
//        {
//            delete[] _values[i];
//        }
//        delete[] _values;
//    }
//}
//
//template<typename T>
//void Matrix<T>::PrintMatrix()
//{
//    for (int i = 0; i < _sizeX; ++i)
//    {
//        for (int j = 0; j < _sizeY; ++j)
//        {
//            std::cout << _values[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//}


