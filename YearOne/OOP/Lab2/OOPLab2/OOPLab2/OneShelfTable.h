#pragma once
#include "Rectangle.h"
// Rectangle.h
class OneShelfTable : public Rectangle
{
private:
	int _height;

	int GetCapacity();

public:
	OneShelfTable(int length, int width, int height);

	void PrintCharacteristics();
};

