#include <iostream>
#include <iomanip>

using namespace std;

void PrintFunc(bool X, bool Y, bool Z);
void PrintHead();
void CheckFict();
bool Func(bool X, bool Y, bool Z);
void CheckPost();
bool CheckMClass();

int main()
{

	PrintHead();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int l = 0; l < 2; l++)
			{
				PrintFunc(i, j, l);
			}
		}
	}

	cout << "  +" << setw(58) << setfill('-') << "+" << endl;

	CheckFict();
	CheckPost();
}

void CheckFict()
{
	cout << endl;
	for (int y = 0; y < 2; y++)
	{
		for (int z = 0; z < 2; z++)
		{
			if (Func(0, y, z) != Func(1, y, z))
			{
				cout << "   X is not fict\n";
				break;
			}
		}
	}

	for (int x = 0; x < 2; x++)
	{
		for (int z = 0; z < 2; z++)
		{
			if ((Func(x, 0, z) != Func(x, 1, z)) == 1)
			{
				cout << "   Y is not fict\n";
				break;
			}
		}
	}

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			if ((Func(x, y, 0) != Func(x, y, 1)) == 1)
			{
				cout << "   Z is not fict\n";
				break;
			}
		}
	}
}

void PrintHead()
{
	cout << endl << "  +" << setw(58) << setfill('-') << "+" << endl;
	cout << "  |  X  Y  Z  (XZ)  (Y + (XZ))  (X ↔ (Y + (XZ)))  F(X,Y,Z)  |" << endl;
	cout << "  +" << setw(58) << setfill('-') << "+" << endl;
}

bool Func(bool X, bool Y, bool Z)
{
	return !X | (X == (Y | (X && Z)));
}

void PrintFunc(bool X, bool Y, bool Z)
{
	cout << "  |  " << X << "  " << Y << "  " << Z;
	cout << setw(4) << setfill(' ') << (X && Z);
	cout << setw(9) << setfill(' ') << (Y | (X && Z));
	cout << setw(15) << setfill(' ') << (X == (Y | (X && Z)));
	cout << setw(15) << setfill(' ') << (!X | (X == (Y | (X && Z))));
	cout << setw(6) << setfill(' ') << "|" << endl;;
}

void CheckPost() 
{	
	cout << "\n  +----+---+\n";
	cout << "  | T0 | " << ((Func(0, 0, 0) == 0)) << " |\n";
	cout << "  +----+---+\n";

	cout << "  | T1 | " << (Func(1, 1, 1) == 1) << " |\n";
	cout << "  +----+---+\n";

	bool S = 1;


	for (int i = 0; i < 2; i++) 
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++) 
			{
				if (Func(i,j,k) != Func(!i,!j,!k) )
				{
					S = 0;
				}
			}
		}
	}

	cout << "  | S  | " << S << " |\n";
	cout << "  +----+---+\n";

	cout << "  | M  | " << CheckMClass() << " |\n";
	cout << "  +----+---+\n";
}

bool CheckMClass() 
{
	return Func(0, 0, 0) < Func(1, 0, 0) &&
		Func(0, 0, 0) < Func(0, 1, 0) &&
		Func(0, 0, 0) < Func(0, 0, 1) &&
		Func(1, 0, 0) < Func(1, 1, 0) &&
		Func(1, 0, 0) < Func(1, 0, 1) &&
		Func(0, 1, 0) < Func(1, 1, 0) &&
		Func(0, 1, 0) < Func(0, 1, 1) &&
		Func(0, 0, 1) < Func(0, 1, 1) &&
		Func(0, 0, 1) < Func(1, 0, 1) &&
		Func(0, 1, 1) < Func(1, 1, 1) &&
		Func(1, 0, 1) < Func(1, 1, 1) &&
		Func(1, 1, 0) < Func(1, 1, 1);
}
