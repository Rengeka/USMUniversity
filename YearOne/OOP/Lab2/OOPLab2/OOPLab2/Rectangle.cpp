#include "Rectangle.h"
#include <iostream>

using namespace std;

Rectangle::Rectangle(int length, int width) 
{
	_length = length;
	_width = width;
}

int Rectangle::GetArea()
{
	return _width * _length;
}

//Rectangle::Rectangle()
//{
//	_length = 10;
//	_width = 10;
//}

int Rectangle::GetWidth()
{
	return _width;
}

void Rectangle::PrintCharacteristics()
{
	cout << " Length : " << _length << " Width : " << _width << endl;
}

void Rectangle::CompareWithRectangle(Rectangle rect)
{

	int area1 = GetArea();
	int area2 = rect.GetArea();

	if (area1 > rect.GetArea())
	{
		cout << " Rectangle 1 is larger than Rectangle 2" << endl;
		cout << " Rectanle 1 can fit Rectangle 2 (" << area1 / area2 << ") times" << endl;;
	}
	else if (area1 < area2)
	{
		cout << " Rectangle 2 is larger than Rectangle 1" << endl;
		cout << " Rectanle 2 can fit Rectangle 1 (" << area2 / area1 << ") times" << endl;;
	}
	else
	{
		cout << " Rectangle 1 is simmilar to Rectangle 2" << endl;
		cout << " Rectangles can not fit each other" << endl;
	}
}
