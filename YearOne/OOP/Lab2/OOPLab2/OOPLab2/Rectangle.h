#pragma once
#include "Side.h"

class Rectangle : public Side
{
protected:
	int _width;

public:
	Rectangle(int length, int width);

	Rectangle() :Rectangle(10, 10) {}

	int GetWidth();

	int GetArea();

	virtual void PrintCharacteristics();

	void CompareWithRectangle(Rectangle rect);
};

