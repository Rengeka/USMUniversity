#include "OneShelfTable.h"
#include <iostream>

using namespace std;

OneShelfTable::OneShelfTable(int length, int width, int height)
{
	_length = length;
	_width = width;
	_height = height;
}

int OneShelfTable::GetCapacity()
{
	return GetArea() * _height;
}

void OneShelfTable::PrintCharacteristics()
{
	cout << " Length : " << _length << " Width : " << _width << " Heigtht : " << _height << endl;
}