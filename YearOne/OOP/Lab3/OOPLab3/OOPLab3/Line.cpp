#include "Line.h"
#include <iostream>
#include <fstream>

using namespace std;

int Line::CountLengthOfString(const char* str)
{
	int length = 0;
	while (str[length] != '\0') 
	{
		length++;
	}

	return length;
}

void Line::ClearLine()
{
	delete _str;
	_size = 0;
	_str = nullptr;
}

Line::Line(const Line& line)
{
	_size = line._size;
	_str = new char[_size + 1];
	
	int i = 0;
	while (line._str[i] != '\0')
	{
		_str[i] = line._str[i];
		i++;
	}

	_str[_size] = '\0';
}

Line::Line(Line&& line)
{
	_size = line._size;
	_str = line._str;
	line._str = nullptr;
}

Line::Line(int size) {
	_size = size;
	_str = new char[size];
}

Line::Line(const char* str)
{
	_size = CountLengthOfString(str);

	_str = new char[_size + 1];

	for (int i = 0; i < _size; ++i) {
		_str[i] = str[i];
	}
	_str[_size] = '\0';
}

Line::~Line()
{
	if (_str != nullptr)
	{
		delete _str;
	}
}

char* Line::GetStirng()
{
	return _str;
}

void Line::PrintLine()
{
	int i = 0;
	while (_str[i] != '\0')
	{
		cout << _str[i];
		i++;
	}

	cout << endl;
}

Line Line::operator+(const char* str)
{
	int s = 0;
	while (str[s] != '\0')
	{
		s++;
	}

	int newSize = _size + s + 1;
	char* concString = new char[newSize];

	int i = 0;
	while (_str[i] != '\0')
	{
		concString[i] = _str[i];
		i++;
	}

	int j = 0;
	while (str[j] != '\0')
	{
		concString[i] = str[j];
		i++;
		j++;
	}

	concString[i] = '\0';

	return *new Line(concString);

}

Line Line::operator-(const char* str)
{
	int ammount = 0;
	int i = 0;

	while (_str[i] != '\0')
	{
		int j = 0;
		while (str[j] != '\0')
		{
			if (_str[i] == str[j])
			{
				ammount++;
				break;
			}

			j++;
		}

		i++;
	}

	char* newString = new char[_size - (1 + ammount)];

	i = 0;
	int l = 0;

	while (_str[i] != '\0')
	{
		int j = 0;
		bool add = 1;
		while (str[j] != '\0')
		{
			if (_str[i] == str[j])
			{
				add = 0;
				break;
			}
			j++;
		}

		if (add)
		{
			newString[l] = _str[i];
			l++;
		}


		i++;
	}

	newString[_size - ammount] = '\0';

	return newString;
}

//bool Line::operator>(char* str)
//{
//	int size = CountLengthOfString(str);
//
//	if (_size > size)
//	{
//		return true;
//	}
//	else 
//	{
//		return false;
//	}
//}
//
//bool Line::operator<(char* str)
//{
//	int size = CountLengthOfString(str);
//
//	if (_size < size ) 
//	{
//		return true;
//	}
//	else {
//		return false;
//	}
//}

bool Line::operator>(Line line) 
{
	if (_size > line._size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Line::operator<(Line line) 
{
	if (_size < line._size)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool Line::operator>(const char* str) {
	return 0;
}

	
