#include "Side.h"
#include <iostream>

using namespace std;

int Side::GetLength()
{
	return _length;
}

void Side::PrintCharacteristics()
{
	cout << " Length : " << _length << endl;
}