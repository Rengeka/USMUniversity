#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

int main()
{
	int n, sizeOfWordsArray;
	std::cout << " \nPrint size of string\n";				//	Ввод количества символов
	cin >> n;
	sizeOfWordsArray = 0;

	std::cout << " \n\nPrint string\n";
	char* str = (char*)calloc(n, sizeof(char));			

	for (int i = 0; i < n; i++)							//	Ввод строки
	{

		char c = _getch();
		std::cout << c;
		str[i] = c;
	}

	BlockInput(true);

	bool iscounting = false;

	char** wordsArray = new char*;
	int wordSize = 1;

	for (int i = 0; i < n; i++)							// Алгоритм подсчёта и записи слов в массив
	{
		if (/*(str[i] < 32 or str[i] > 47)*/ ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) && !iscounting)
		{
			char* word = (char*)malloc(sizeof(char) * 2);
			word[0] = str[i];
			word[1] = '\0';
			wordsArray[sizeOfWordsArray] = word;

			iscounting = 1;
			sizeOfWordsArray++;
		}
		else if (/*(str[i] >= 32 and str[i] <= 47) */ !((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) && iscounting)
		{
			iscounting = 0;
			wordSize = 1;
		}
		else if (iscounting)
		{

			char* tempWord = (char*)calloc(wordSize + 1, sizeof(char));
			wordSize++;

			for (int j = 0; j < wordSize - 1; j++)
			{
				tempWord[j] = wordsArray[sizeOfWordsArray - 1][j];
			}

			tempWord[wordSize - 1] = str[i];
			tempWord[wordSize] = '\0';

			wordsArray[sizeOfWordsArray - 1] = tempWord;
		}
	}

	std::cout << " \nWords :\n";

	for (int i = 0; i < sizeOfWordsArray; i++)			// Вывод содержимого массива со словами
	{
		int j = 0;

		while (wordsArray[i][j] != '\0')
		{
			std::cout << " " << wordsArray[i][j];
			j++;
		}

		std::cout << "\n";
	}

	std::cout << "\nAmmount of words = " << sizeOfWordsArray; // Вывод количества слов
}

