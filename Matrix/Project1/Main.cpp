#include <iostream>
#include <vector>

using namespace std;

void switchRows(double a[3][3], double z[3][3], int row);
void putTopRow(double a[3][3], double z[3][3]);
void oneInTheFirstSpot(double a[3][3]);
int LCM(int m, int n);
void multiplyRow(double a[3][3], double z[3][3], int row, int LCM, int termToEqualize);
void subtractRows(double a[3][3], double z[3][3], int subtractor, int subtracted, int termToEqualize);
void printOneRow(double a[3][3], int row);
void printMatrix(double a[3][3], double z[3][3]);
void inverse(double a[3][3], double z[3][3]);


int main()
{
	int inv[3][3] = { { 1, 0, 0 },
					  { 0, 1, 0 },
					  { 0, 0, 1 } };

	int matrix[3][3] = { { 4, 4, 6 },
						 { 1, 3, 5 },
						 { 7, 7, 9 }};

	printMatrix(matrix, inv);
	cout << endl;
	inverse(matrix, inv);
	printMatrix(matrix, inv);

	system("pause");
	return 0;
}

void switchRows(int a[3][3], int z[3][3], int row)
{
	int temp;
	int invTemp;
	for (int column = 0; column < 3; column++)
	{
		temp = a[row][column];
		invTemp = z[row][column];
		a[row][column] = a[0][column];
		z[row][column] = z[0][column];
		a[0][column] = temp;
		z[0][column] = temp;
	}
}

void putTopRow(int a[3][3], int z[3][3])
{
	int i = 1;
	while (i < 3 && a[0][0] != 1)
	{
		if (a[i][0] == 1)
			switchRows(a, z, i);
		i++;
	}
}

void oneInTheFirstSpot(int a[3][3])
{
	int divisor = a[0][0];
	for (int i = 0; i < 3; i++)
	{
		a[0][i] /= divisor;
	}
}

int LCM(int m, int n)
{
	if (m == 0 || n == 0)
		return 0;
	else
	{
		int x = abs(m);
		int y = abs(n);

		int i = 1;
		int j = 1;

		//x is always greater than or equal to y
		if (x < y)
		{
			int w = x;
			x = y;
			y = w;
		}

		bool found = false;

		// if the second number times the multiple is smaller than the first
		// index the second

		//if the first times it's multiple is smaller
		//index the first

		while (found == false)
		{
			if (i == y && j == x)
				found = true;
			else
			{
				while (x*i != y*j)
				{
					(x*i > y*j) ? j++ : i++;
				}
				found = true;
			}
		}

		return x*i;
	}
}

void multiplyRow(int a[3][3], int z[3][3], int row, int LCM, int termToEqualize)
{
	int multiplier;

	multiplier = (LCM == 0) ? 0 : (LCM / a[row][termToEqualize]);

	for (int i = 0; i < 3; i++)
	{
		a[row][i] *= multiplier;
		z[row][i] *= multiplier;
	}
}


void subtractRows(int a[3][3], int z[3][3], int subtractor, int subtracted, int termToEqualize)
{
	int temp[3];
	for (int b = 0; b < 3; b++)
		temp[b] = a[subtracted][b];

	multiplyRow(a, z, subtracted, LCM(a[subtracted][termToEqualize], a[subtractor][termToEqualize]), termToEqualize);
	multiplyRow(a, z, subtractor, LCM(a[subtracted][termToEqualize], a[subtractor][termToEqualize]), termToEqualize);

	for (int i = 0; i < 3; i++)
	{
		a[subtractor][i] -= a[subtracted][i];
		a[subtracted][i] = temp[i];
	}

}

void printOneRow(int a[3][3], int row)
{
	for (int i = 0; i < 3; i++)
	{
		cout << a[row][i] << ", ";
	}
	cout << endl;
}

void printMatrix(int a[3][3], int z[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << z[i][j] << " ";
		cout << endl;
	}
}

void inverse(int a[3][3], int z[3][3])
{
	oneInTheFirstSpot(a);

	subtractRows(a, z, 1, 0, 0);
	subtractRows(a, z, 2, 0, 0);
	subtractRows(a, z, 0, 1, 1);
	subtractRows(a, z, 0, 2, 2);
	subtractRows(a, z, 1, 2, 2);




}