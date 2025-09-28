#pragma once
#include <string>

using namespace std;

class Line
{
private:
	int _size;

	char* _str;

public:

	Line(const char* str);

	Line(int size);

	Line(const Line& line);

	Line(Line&& line);

	Line operator+(const char* str);

	Line operator-(const char* str);

	bool operator>(Line line);

	bool operator<(Line line);

	bool operator>(char* str);

	bool operator>(const char* str);

	bool operator<(char* str);

	char* GetStirng();

	void PrintLine();

	~Line();

	int CountLengthOfString(const char* str);

	void ClearLine();

	friend ostream& operator << (ostream& os, Line& line);


};

