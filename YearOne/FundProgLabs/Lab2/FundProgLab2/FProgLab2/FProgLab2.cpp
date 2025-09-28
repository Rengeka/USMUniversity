#include <iostream>

void PrintArray(int* ar, int n)   // Функция вывода массива
{
	for (int i = 0; i < n; i++)
	{
		std::cout << " Number : " << i << "\t Value : " << ar[i] << std::endl;
	}
}

void CountSameNumbers(int* ar, int n)  // Функция выполняющая саму задачу 
{
	{
		int xGlob = 1;
		int xLoc = 1;
		int el = 0;

		for (int i = 1; i < n; i++)
		{
			if (ar[i] == ar[i - 1])
			{
				xLoc += 1;
			}
			else
			{
				if (xLoc > xGlob)
				{
					xGlob = xLoc;
					el = i - 1;
				}
				xLoc = 1;
			}
		}

		std::cout << std::endl << " Row : " << el << std::endl << " Ammount : " << xGlob << std::endl << std::endl;
	}
}
void InitializeArray(int* ar, int n) // Функция инициализации массива
{
	for (int i = 0; i < n; i++)
	{
		std::cout << " Enter " << i << " element" << std::endl;
		std::cin >> ar[i];
	}
}

int main()
{
	int c;

	std::cout << "Choose " << std::endl; // Выбор способа ввода массива
	std::cout << " 1 - Prefabricated array " << std::endl;
	std::cout << " 2 - Random array " << std::endl;
	std::cout << " 3 - Enter custom array " << std::endl;
	std::cin >> c;
	std::cout << std::endl;

	switch (c)
	{
	case 1:  // Использование предзаготовленного массива
	{
		int ar[] = { 1,2,2,4,5,6,7,8,9,9,9,9,1,1,1,2,3,4,5 };
		system("cls"); printf("\n");
		PrintArray(ar, 19);
		CountSameNumbers(ar, 19);
		break;
	}
	case 2:  // Использование случайного массива
	{
		int n;
		std::cout << " Enter size" << std::endl;
		std::cin >> n;
		int* ar = (int*)calloc(n, sizeof(int));

		srand(time(NULL));

		for (int i = 0; i < n; i++)
		{
			ar[i] = rand() % 10;
		}

		system("cls"); printf("\n");
		PrintArray(ar, n);
		CountSameNumbers(ar, n);
		break;
	}
	case 3: // Использование заданного пользователем массива
	{
		int n;
		std::cout << " Enter size" << std::endl;
		std::cin >> n;
		int* ar = (int*)calloc(n, sizeof(int));
		InitializeArray(ar, n);
		system("cls"); printf("\n");
		PrintArray(ar, n);
		CountSameNumbers(ar, n);
	}
	}
}

