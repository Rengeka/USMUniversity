#pragma once
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

enum JobTitle
{
	Programmer,
	Tester,
	HR,
	TeamLead,
	GameDesigner,
	Other
};

class Worker
{
private:

	// Fields

	string _name;
	tm _birthDate;
	tm _hiringDate;
	JobTitle _job;
	int _salary;

public:

	// Constructors

	Worker();

	Worker(string name, tm birthDate, tm hiringDate, JobTitle job, int salary);

	Worker(string str);

	// Getters

	string GetName();
	tm GetBirthDate();
	tm GetHiringDate();
	JobTitle GetJobTitle();
	int GetSalary();

	// Setters

	void SetSalary(int salary);
	void SetName(string name);
	void SetHiringDate(tm date);
	void SetBirthDate(tm date);
	void SetJobTitle(JobTitle job);

	// Destructor

	~Worker();

};

