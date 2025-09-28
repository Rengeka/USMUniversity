#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Matrix
{
private:
	T** _values;
	int _sizeX;
	int _sizeY;

public:

    int GetSizeX() 
    {
        return _sizeX;
    }

    int GetSizeY() 
    {
        return _sizeY;
    }


    T** GetValues() 
    {
        return _values;
    }

    void SetValues(T* values []) 
    {

        for (int i = 0; i < _sizeX; i++) 
        {
            for (int j = 0; j < _sizeY; j++) 
            {
                _values[i][j] = values[i][j];
            }
        }
    }

    Matrix(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY)
    {
        _values = new T * [_sizeX];
        for (int i = 0; i < _sizeX; ++i)
        {
            _values[i] = new T[_sizeY];
        }
    }

    Matrix(int sizeX, int sizeY, T** values) : _sizeX(sizeX), _sizeY(sizeY), _values(values) {}


    ~Matrix()
    {
        cout << "DESTRUCTOR IS WORKING\n";
        if (_values != nullptr)
        {
            for (int i = 0; i < _sizeX; ++i)
            {
                delete[] _values[i];
            }
            delete[] _values;
        }
    }

    void PrintMatrix()
    {
        for (int i = 0; i < _sizeX; ++i)
        {
            for (int j = 0; j < _sizeY; ++j)
            {
                std::cout << _values[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix<T>& operator+(Matrix<T>& matrix) 
    {
        if (_sizeX == matrix.GetSizeX() && _sizeY == matrix.GetSizeY())
        {
            Matrix<T>* mat = new Matrix<T>(_sizeX, _sizeY);

            for (int i = 0; i < _sizeX; i++) 
            {
                for (int j = 0; j < _sizeY; j++) 
                {
                    mat->_values[i][j] = _values[i][j] + matrix.GetValues()[i][j];
                }
            }

            return *mat;

        }
        else 
        {
            throw 0;
        }
    }

    Matrix<T>& operator-(Matrix<T>& matrix)
    {
        if (_sizeX == matrix.GetSizeX() && _sizeY == matrix.GetSizeY())
        {

            Matrix<T>* mat = new Matrix<T>(_sizeX, _sizeY);

            for (int i = 0; i < _sizeX; i++)
            {
                for (int j = 0; j < _sizeY; j++)
                {
                    mat->_values[i][j] = _values[i][j] - matrix.GetValues()[i][j];
                }
            }

            return *mat;

        }
        else
        {
            throw 0;
        }
    }

    Matrix<T>& operator*(Matrix<T>& matrix)
    {
        if (_sizeX == matrix.GetSizeX() && _sizeY == matrix.GetSizeY())
        {
            Matrix<T>* mat = new Matrix<T>(_sizeX, _sizeY);

            for (int i = 0; i < _sizeX; i++)
            {
                for (int j = 0; j < _sizeY; j++)
                {
                    mat->_values[i][j] = _values[i][j] * matrix.GetValues()[i][j];
                }
            }

            return *mat;

        }
        else
        {
            throw 0;
        }
    }

    friend ostream& operator << (ostream& os, Matrix<T>&& matrix);

};

