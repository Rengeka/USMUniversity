#include <iostream>	  // Console
#include <string>	  // String 
#include "Worker.h"
#include <conio.h>    // getch
#include <time.h>     // time
#include <stdio.h>    // msize
#include <algorithm>  // sort
#include <vector>   
#include <fstream>    // working with files 

using namespace std;

Worker* EnterWorkerData();

void PrintData(Worker** workers);

void StartApplication();

void FindBySalary(Worker** workers);

void PrintFirstXWorkers(Worker** workers);

Worker** DeleteElement(Worker** workers);

void PrintWorkerData(Worker* worker);

Worker** AddNewWorker(Worker** workers);				// Adds new worker to the end of array

Worker** AddNewWorker(Worker** workers, int position);  // Adds new worker to the chosen of array

void SortByName(Worker** workers);

Worker** GetDataFromFile(string filename);

void SaveToFile(string fileName, Worker** workers);

void DeleteWorkers(Worker** workers);


int main()
{
	/*Дан класс Рабочий с приватными(private) полями: Имя, дата, дата приема на работу,
		должность, зарплата и публичные поля : конструктор без параметров, конструктор с
		параметрами, деструктор и вспомогательные функции.Создать программу, в кот.Объявляется
		массив объектов этого класса и меню(каждый пункт меню – отдельная функция) :
		1) Ввести элементы массива с клавиатуры;
		2) Вывести на экран элементы массива(объекты);
		3) Сортировать в алфавитном порядке по полю Имя;
		4) Вывести на экран элементы, для кот.зарплата меньше чем значение Х(вводится с клавиатуры);
		5) Добавить на позицию К новый элемент(К вводится с клавиатуры);
		6) Удалить первый элемент, для которого мы знаем должность(вводим должность и подолжности удаляем первого попавшегося);
		7) Записать элементы массива в файл;
		8) Вывести на экран первые N элементов из файла(N с клавиатуры).*/

	StartApplication();

}

void StartApplication()
{

	Worker** workers;

	cout << endl << "  Press E to enter worker data from keyboard"
		<< endl << "  Press R to create random worker data"
		<< endl << "  Press F to get data from file" << endl;


	char key = _getche();

	switch (key)
	{
	case 'e':
	{
		system("CLS");
		cout << endl << "  Enter ammount of workers: ";

		int n;
		cin >> n;

		//workers = (Worker**)calloc(n, sizeof(Worker*));
		workers = new Worker * [n];


		for (int i = 0; i < n; i++)
		{
			system("CLS");
			workers[i] = EnterWorkerData();
		}

		break;
	}
	case 'r':
	{
		srand(time(NULL));

		int n = 10;

		//workers = (Worker**)calloc(n, sizeof(Worker*));
		workers = new Worker * [n];

		for (int i = 0; i < n; i++)
		{
			workers[i] = new Worker();
		}

		break;
	}
	case 'f':
	{
		string path;

		system("CLS");
		cout << endl << " Enter path to file : ";
		cin >> path;

		workers = GetDataFromFile(path);

		break;
	}
	default:
	{
		int n = 10;

		//workers = (Worker**)calloc(n, sizeof(Worker*));
		workers = new Worker * [n];

		for (int i = 0; i < n; i++)
		{
			workers[i] = new Worker();
		}

		break;
	}

	}

	bool isExecuting = true;

	while (isExecuting)
	{
		system("CLS");
		cout << endl << "  Press P to print data" << endl;
		cout << "  Press X to find people by salary" << endl;
		cout << "  Press F to print first x workers data" << endl;
		cout << "  Press D to delete first worker data with chosen Job title" << endl;
		cout << "  Press A to add new worker data" << endl;
		cout << "  Press C to add new worker data on chosen position" << endl;
		cout << "  Press S to sort workers by name" << endl;
		cout << "  Press T to write data to file" << endl;
		cout << "  Press G to get workers from file" << endl;
		cout << "  Press N to terminate application" << endl;

		char input = _getche();

		switch (input)
		{
		case 'p':
		{
			system("CLS");
			PrintData(workers);
			break;
		}
		case 'x':
		{
			system("CLS");
			FindBySalary(workers);
			break;
		}
		case 'f':
		{
			system("CLS");
			PrintFirstXWorkers(workers);
			break;
		}
		case 'd':
		{
			system("CLS");
			workers = DeleteElement(workers);
			break;
		}
		case 'a':
		{
			system("CLS");
			workers = AddNewWorker(workers);
			break;
		}
		case 'c':
		{
			system("CLS");
			cout << "Enter position" << endl;;
			int pos;
			cin >> pos;
			workers = AddNewWorker(workers, pos);
			break;
		}
		case 's':
		{
			system("CLS");
			SortByName(workers);
			break;
		}
		case 't':
		{
			string path;

			system("CLS");
			cout << endl << " Enter path to file : ";
			cin >> path;

			SaveToFile(path, workers);
			break;
		}
		case 'g':
		{
			DeleteWorkers(workers);
			string path;

			system("CLS");
			cout << endl << " Enter path to file : ";
			cin >> path;

			workers = GetDataFromFile(path);
			cout << endl << "Press any key to continue";
			break;
		}
		case 'n':
		{
			system("CLS");
			isExecuting = false;
			cout << endl << " Thank you for enjoying my laboratory work!" << endl << " Press any key to terminate app";
			break;
		}
		default:
		{
			break;
		}

		}
		_getche();
	}
}

Worker** GetDataFromFile(string filename)
{
	ifstream inFile(filename);

	if (inFile.is_open())
	{

		string str;

		int i = 0;
		while (getline(inFile, str))
		{
			i++;
		}

		str = "";

		Worker** workers = new Worker * [i];
		i = 0;

		inFile = ifstream(filename);

		while (getline(inFile, str))
		{
			workers[i] = new Worker(str);
			i++;
		}

		inFile.close();

		return workers;
	}
	else
	{
		cerr << "Unable to open the file.\n";
		return NULL;
	}
}

void SaveToFile(string fileName, Worker** workers)
{
	ofstream outFile;
	outFile.open(fileName);
	if (outFile.is_open())
	{
		int size = _msize(workers) / sizeof(workers[0]);
		for (int i = 0; i < size; i++)
		{
			outFile << workers[i]->GetName() << " " << workers[i]->GetBirthDate().tm_mday << " " << workers[i]->GetBirthDate().tm_mon << " " << workers[i]->GetBirthDate().tm_year
				<< " " << workers[i]->GetHiringDate().tm_mday << " " << workers[i]->GetHiringDate().tm_mon << " " << workers[i]->GetHiringDate().tm_year
				<< " " << workers[i]->GetJobTitle() << " " << workers[i]->GetSalary() << endl;
		}

		cout << "File has been written" << std::endl;
	}
	else 
	{
		cout << "File hasn't been written" << std::endl;
	}

	outFile.close();
	cout << endl << "Press any key to continue";
}

void SortByName(Worker** workers)
{
	int size = _msize(workers) / sizeof(workers[0]);

	vector<string> names;

	for (int i = 0; i < size; i++)
	{
		names.push_back(workers[i]->GetName());
	}

	sort(names.begin(), names.end());

	for (int i = 0; i < size; i++)
	{
		cout << names[i] << endl;
	}

}

Worker** AddNewWorker(Worker** workers)
{
	int size = _msize(workers) / sizeof(workers[0]);

	//Worker** workers2 = (Worker**)calloc(size + 1, sizeof(workers[0]));
	Worker** workers2 = new Worker * [size + 1];

	for (int i = 0; i < size; i++)
	{
		workers2[i] = workers[i];
	}

	workers2[size] = EnterWorkerData();

	cout << endl << "Press any key to continue";
	return workers2;
}

Worker** AddNewWorker(Worker** workers, int position)
{
	int size = _msize(workers) / sizeof(workers[0]);

	if (position < size && position >= 0)
	{
		//	Worker** workers2 = (Worker**)calloc(size + 1, sizeof(workers[0]));
		Worker** workers2 = new Worker * [size + 1];

		for (int i = 0; i < position; i++)
		{

			workers2[i] = workers[i];

		}

		workers2[position] = EnterWorkerData();

		if (position < size - 1)
		{
			for (int i = position + 1; i <= size; i++)
			{
				workers2[i] = workers[i - 1];
			}
		}

		return workers2;
	}
	else
	{
		return workers;
	}
}

Worker** DeleteElement(Worker** workers)
{
	cout << endl << " Enter Job title" << endl;
	cout << "   0 - Programmer" << endl;
	cout << "   1 - Tester" << endl;
	cout << "   2 - HR" << endl;
	cout << "   3 - TeamLead" << endl;
	cout << "   4 - GameDesigner" << endl;
	cout << "   5 - Other" << endl;

	int index;
	JobTitle job;
	cin >> index;
	job = (JobTitle)index;

	int size = _msize(workers) / sizeof(workers[0]);

	//Worker** workers2 = (Worker**)calloc(size - 1, sizeof(workers[0]));
	Worker** workers2 = new Worker * [size - 1];

	int j = 0;
	for (int i = 0; i < size; i++)
	{
		if (workers[i]->GetJobTitle() == job && i == j)
		{
			delete workers[i];
			i++;
		}

		workers2[j] = workers[i];

		j++;
	}

	cout << endl << "Press any key to continue";
	_getche();

	return workers2;
}

void FindBySalary(Worker** workers)
{
	system("CLS");
	cout << endl << " Enter salary" << endl << endl << " ";
	int size = _msize(workers) / sizeof(workers[0]);
	int sal;
	cin >> sal;

	for (int i = 0; i < size; i++)
	{
		if (workers[i]->GetSalary() >= sal)
		{
			cout << endl << " " << workers[i]->GetName() << endl
				<< "   Salary : " << workers[i]->GetSalary() << endl;
		}
	}

	cout << endl << "Press any key to continue";
}

void PrintWorkerData(Worker* worker)
{
	cout << endl << " " << worker->GetName() << endl << "   Birht date : " << worker->GetBirthDate().tm_mday
		<< "." << worker->GetBirthDate().tm_mon + 1 << "." << worker->GetBirthDate().tm_year
		<< endl << "   Hiring date : " << worker->GetHiringDate().tm_mday << "." << worker->GetHiringDate().tm_mon + 1
		<< "." << worker->GetHiringDate().tm_year << endl << "   Job title : ";

	switch (worker->GetJobTitle())
	{
	case 0:
	{
		cout << "Programmer" << endl;
		break;
	}
	case 1:
	{
		cout << "Tester" << endl;;
		break;
	}
	case 2:
	{
		cout << "HR" << endl;;
		break;
	}
	case 3:
	{
		cout << "Team Lead" << endl;;
		break;
	}
	case 4:
	{
		cout << "Game Designer" << endl;;
		break;
	}
	case 5:
	{
		cout << "Other" << endl;
		break;
	}
	}

	cout << "   Salary : " << worker->GetSalary() << endl;
}

void PrintData(Worker** workers)
{

	int size = _msize(workers) / sizeof(workers[0]);
	for (int i = 0; i < size; i++)
	{
		PrintWorkerData(workers[i]);
	}
	cout << endl << "Press any key to continue";
}

void PrintFirstXWorkers(Worker** workers)
{
	int n;
	cout << endl << " Enter ammount of expected workers" << endl << endl << " ";
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		PrintWorkerData(workers[i]);
	}

	cout << endl << "Press any key to continue";
}

Worker* EnterWorkerData()
{
	string name;
	cout << "Enter name" << endl;
	cin >> name;

	tm birthDate;
	cout << "Enter birth year" << endl;
	cin >> birthDate.tm_year;

	cout << "Enter birth month" << endl;
	cin >> birthDate.tm_mon;

	cout << "Enter birth day" << endl;
	cin >> birthDate.tm_mday;

	tm hiringDate;
	cout << "Enter hiring year" << endl;
	cin >> hiringDate.tm_year;

	cout << "Enter hiring month" << endl;
	cin >> hiringDate.tm_mon;

	cout << "Enter hiring day" << endl;
	cin >> hiringDate.tm_mday;

	cout << "Enter job title" << endl;
	int j;
	cin >> j;

	int salary;
	cout << "Enter salary" << endl;
	cin >> salary;

	return  new Worker(name, birthDate, hiringDate, (JobTitle)j, salary);

}

void DeleteWorkers(Worker** workers)
{
	int size = _msize(workers) / sizeof(workers[0]);

	for (int i = 0; i < size; i++)
	{
		delete workers[i];
	}

	delete workers;
}