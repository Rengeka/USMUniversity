#include <iostream>           // Стандартный заголовок
#include <iomanip>            // Подключение функций для работы с консолью вывода
#define _USE_MATH_DEFINES     // Определяем стандартные математические константы
#define M_PI_3
#include <math.h>             // Подключение математических функций
//#include <conio.h>			  // Подключение функций для работы с консолью вывода

void PrintHead()              // Функция вывода начальной информации и шапки таблицы
{
	std::cout << std::endl;
	std::cout << "  [-PI/2; PI/2]" << std::endl << std::endl 
		<< "  Step +PI/10" << std::endl << std::endl;
	
	std::cout << "  ===============================" << std::endl;
	printf(" ||     x     ||        y       ||\n");
	std::cout << "  ===============================" << std::endl;
}

double MathFunc(double* x)    // Математическая функция
{
	if (*x <= M_PI / 3)      
	{						  // Промежуток от -бесконечности до PI/3
		return exp(cos(*x));

	}
	else if (*x > M_PI / 3)   // Промежуток от PI/3 до бесконечности
	{
		return cos(exp(*x));

	}
	else
	{
		return NULL;
	}
}

void PrintResult(double* x, double y)  // Функция вывода результата в консоль
{
	std::cout << std::setiosflags(std::ios::left);
	std::cout << " || ";
	std::cout.width(10);
	std::cout << *x << "||" << "    " << std::setw(9) << y;
	printf("\t||\n");
}

int main()
{
	double* x = (double*)malloc(sizeof(double));   // Обьявление переменных
	*x = -M_PI / 2;
	PrintHead();

	while (*x >= (-M_PI / 2) and *x <= (M_PI / 2)) // Цикл с шагом в PI/10
	{
		PrintResult(x, MathFunc(x));
		*x += M_PI / 10;
	}

	std::cout << "  ===============================" << std::endl; // Завершение таблицы

	return 0;
}


