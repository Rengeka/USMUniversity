#include <iostream>
#include <iomanip>

using namespace std;

void Func(bool P, bool Q, bool R);
void PrintHead();

int main()
{

	PrintHead();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int l = 0; l < 2; l++)
			{
				Func(i, j, l);
			}
		}
	}

	cout << "  +" << setw(103) << setfill('-') << "+" << endl;
}

void PrintHead()
{
	cout << endl << "  +" << setw(103) << setfill('-') << "+" << endl;
	cout << "  |  P  Q  R  (P ↔ Q)  (P ↔ R)  (Q ↔ R)  ((P ↔ Q) ↔ (P ↔ R))  (((P ↔ Q) ↔ (P ↔ R)) ↔ (Q ↔ R))  F(P,Q,R)  |" << endl;
	cout << "  +" << setw(103) << setfill('-') << "+" << endl;
}

void Func(bool P, bool Q, bool R)
{
	cout << "  |  " << P << "  " << Q << "  " << R;
	cout << setw(6) << setfill(' ') << (P == Q);
	cout << setw(9) << setfill(' ') << (P == R);
	cout << setw(9) << setfill(' ') << (R == Q);
	cout << setw(15) << setfill(' ') << ((P == Q) == (P == R));
	cout << setw(27) << setfill(' ') << (((P == Q) == (P == R)) == (Q == R));
	cout << setw(22) << setfill(' ') << ((((P == Q) == (P == R)) == (Q == R)) == R);
	cout << setw(6) << setfill(' ') << "|" << endl;;
}
