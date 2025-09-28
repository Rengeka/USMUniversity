#include "Worker.h"
#include <time.h>   // time
#include <stdlib.h> // srand
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// Getters

string Worker::GetName()
{
	return _name;
}

tm Worker::GetBirthDate()
{
	return _birthDate;
}

tm Worker::GetHiringDate()
{
	return _hiringDate;
}

JobTitle Worker::GetJobTitle()
{
	return _job;
}

int Worker::GetSalary()
{
	return _salary;
}

// Setters

void Worker::SetSalary(int salary)
{
	_salary = salary;
}

void Worker::SetName(string name)
{
	_name = name;
}

void Worker::SetBirthDate(tm date)
{
	_birthDate = date;
}

void Worker::SetHiringDate(tm date)
{
	_hiringDate = date;
}

void Worker::SetJobTitle(JobTitle job)
{
	_job = job;
}

// Constructors

Worker::Worker()
{
	string names[] = { "John", "Peter", "Donald", "Kate", "Jane", "Marry", "Antony", "Clara", "Michael" };
	string surenames[] = { "Trump", "Smith", "Johnson", "Brown", "Jones", "Miller", "Davis", "Maguire", "Kane" };

	_name = names[rand() % 9] + " " + surenames[rand() % 9];

	_birthDate.tm_year = rand() % 60 + 1940;
	_birthDate.tm_mon = rand() % 12;
	_birthDate.tm_mday = rand() % 31 + 1;

	_hiringDate.tm_year = rand() % (2024 - (_birthDate.tm_year + 18)) + (_birthDate.tm_year + 18);
	_hiringDate.tm_mon = rand() % 12;
	_hiringDate.tm_mday = rand() % 31 + 1;

	_salary = rand() % 1000 + 1000;

	_job = (JobTitle)(rand() % 6);
}

/*Worker::Worker(string name, tm birthDate, tm hiringDate, JobTitle job, int salary)
{
	_name = name;
	_birthDate = birthDate;
	_hiringDate = hiringDate;
	_job = job;
	_salary = salary;
}*/

Worker::Worker(string name, tm birthDate, tm hiringDate, JobTitle job, int salary)
	: _name(name),
	_birthDate(birthDate),
	_hiringDate(hiringDate),
	_job(job),
	_salary(salary) {}

Worker::Worker(string str)
{
	istringstream iss(str);

	int job;

	iss >> _name >> _birthDate.tm_mday >> _birthDate.tm_mon >> _birthDate.tm_year
		>> _hiringDate.tm_mday >> _hiringDate.tm_mon >> _hiringDate.tm_year
		>> job >> _salary;

	_job = JobTitle(job);
}

// Destructor

Worker::~Worker()
{

	cout << "Destructor is working" << endl;
}