#include <iostream>
#include "Side.h"
#include "Rectangle.h"
#include "OneShelfTable.h"

using namespace std;

void CompareArea(Rectangle rect1, Rectangle rect2);

int main()
{
	/*Создайте иерархию классов Сторона – Прямоугольник – Тумбочка с одной полкой.
	
	Класс Прямоугольник должен содержать метод для вычисления площади прямоугольника.

	Класс Тумбочка должен содержать метод для определения вместимости.

	Последние два класса в иерархии должны иметь конструкторы.
	
	Создайте метод MAIN, в котором создается 2 прямоугольника(т.е. 2 объекта класса Прямоугольник), 
	определяется какой из прямоугольников больше и сколько раз меньший прямоугольник 
	входит в больший.
	
	Необходимо также показывать все характеристики создаваемых объектов.*/

	Rectangle rect = *new Rectangle();
	rect.PrintCharacteristics();

	Rectangle rect1 = *new Rectangle(5, 12);
	Rectangle rect2 = *new Rectangle(10, 12);
	
	rect1.PrintCharacteristics();
	rect2.PrintCharacteristics();

	rect.CompareWithRectangle(rect1);

	cout << endl;
	CompareArea(rect1, rect2);
}

void CompareArea(Rectangle rect1, Rectangle rect2)
{
	int area1 = rect1.GetArea();
	int area2 = rect2.GetArea();

	if (area1 > rect2.GetArea())
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