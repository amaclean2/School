#include <iostream>
#include <time.h>
#include <string>

using namespace std;

void createACube(string a[6][3][3])
{
	int b;
	for (int i = 0; i < 6; i++)
	{
		b = 0;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				b = (3 * j) + k;
				a[i][j][k] = '0' + b;

				
				switch (i)
				{
				case 0:
					a[i][j][k] += 'w';
					break;
				case 1:
					a[i][j][k] += 'r';
					break;
				case 2:
					a[i][j][k] += 'b';
					break;
				case 3:
					a[i][j][k] += 'o';
					break;
				case 4:
					a[i][j][k] += 'g';
					break;
				case 5:
					a[i][j][k] += 'y';
					break;
				}
			}
		}
	}
}

void printCube(const string a[6][3][3])
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
				cout << a[i][j][k] << " ";
			cout << "  ";
		}
		cout << endl;
	}

	cout << endl;

	for (int j = 0; j < 3; j++)
	{
		for (int i = 3; i < 6; i++)
		{
			for (int k = 0; k < 3; k++)
				cout << a[i][j][k] << " ";
			cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void setTwoEqual(string a[6][3][3], string b[6][3][3])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
				b[i][j][k] = a[i][j][k];
		}
	}
}

void top(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{
		a[1][0][j] = temp[2][0][i];
		a[2][0][i] = temp[3][0][i];
		a[3][0][i] = temp[4][0][i];
		a[4][0][i] = temp[1][0][i];

		//roatate face
		a[0][0][i] = temp[0][j][0];
		a[0][i][2] = temp[0][0][i];
		a[0][2][j] = temp[0][i][2];
		a[0][j][0] = temp[0][2][j];
		j--;
	}
}

void topI(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{
		a[2][0][i] = temp[1][0][i];
		a[3][0][i] = temp[2][0][i];
		a[4][0][i] = temp[3][0][i];
		a[1][0][i] = temp[4][0][i];

		//roatate face
		a[0][j][0] = temp[0][0][i];
		a[0][0][i] = temp[0][i][2];
		a[0][i][2] = temp[0][2][j];
		a[0][2][j] = temp[0][j][0];
		j--;
	}
}

void front(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// these are good

		a[5][0][i] = temp[2][i][0];
		a[2][i][0] = temp[0][2][i];
		a[0][2][i] = temp[4][j][2];
		a[4][i][2] = temp[5][0][i];

		//rotate face
		a[1][0][i] = temp[1][j][0];
		a[1][i][2] = temp[1][0][i];
		a[1][2][j] = temp[1][i][2];
		a[1][j][0] = temp[1][2][j];
		j--;
	}
}

void frontI(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{
		a[2][i][0] = temp[5][0][i];
		a[0][2][i] = temp[2][i][0];
		a[4][j][2] = temp[0][2][i];
		a[5][0][i] = temp[4][i][2];

		//rotate face
		a[1][j][0] = temp[1][0][i];
		a[1][0][i] = temp[1][i][2];
		a[1][i][2] = temp[1][2][j];
		a[1][2][j] = temp[1][j][0];
		j--;
	}
}

void left(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// done... I think

		a[1][i][0] = temp[0][i][0];
		a[5][i][0] = temp[1][i][0];
		a[3][j][2] = temp[5][i][0];
		a[0][i][0] = temp[3][j][2];

		//rotate face
		a[4][0][i] = temp[4][j][0];
		a[4][i][2] = temp[4][0][i];
		a[4][2][j] = temp[4][i][2];
		a[4][j][0] = temp[4][2][j];
		j--;
	}
}

void leftI(string a[6][3][3])
{
	string temp[6][3][3];
	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{
		// done
		a[0][i][0] = temp[1][i][0];
		a[1][i][0] = temp[5][i][0];
		a[5][i][0] = temp[3][j][2];
		a[3][j][2] = temp[0][i][0];

		//rotate face
		a[4][j][0] = temp[4][0][i];
		a[4][0][i] = temp[4][i][2];
		a[4][i][2] = temp[4][2][j];
		a[4][2][j] = temp[4][j][2];
		j--;
	}
}

void back(string a[6][3][3])
{
	string temp[6][3][3];
	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// done

		a[0][0][i] = temp[4][j][2];
		a[2][i][0] = temp[0][0][i];
		a[5][2][i] = temp[2][i][0];
		a[4][j][2] = temp[5][2][i];

		//rotate face
		a[3][0][i] = temp[3][j][0];
		a[3][i][2] = temp[3][0][i];
		a[3][2][j] = temp[3][i][2];
		a[3][j][0] = temp[3][2][j];
		j--;
	}
}

void backI(string a[6][3][3])
{
	string temp[6][3][3];
	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// done

		a[4][j][2] = temp[0][0][i];
		a[0][0][i] = temp[2][i][0];
		a[2][i][0] = temp[5][2][i];
		a[5][2][i] = temp[4][j][2];

		//rotate face
		a[3][j][0] = temp[3][0][i];
		a[3][0][i] = temp[3][i][2];
		a[3][i][2] = temp[3][2][j];
		a[3][2][j] = temp[3][j][0];
		j--;
	}
}

void right(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);
	
	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// done

		a[0][i][2] = temp[1][i][2];
		a[3][i][0] = temp[0][j][2];
		a[5][i][2] = temp[3][i][0];
		a[1][i][2] = temp[5][i][2];

		//rotate face
		a[2][0][i] = temp[2][j][0];
		a[2][i][2] = temp[2][0][i];
		a[2][2][j] = temp[2][i][2];
		a[2][j][0] = temp[2][2][j];
		j--;
	}
	
}

void rightI(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// 

		a[1][i][2] = temp[0][i][2];
		a[0][j][2] = temp[3][i][0];
		a[3][i][0] = temp[5][i][2];
		a[5][i][2] = temp[1][i][2];

		//rotate face
		a[2][j][0] = temp[2][0][i];
		a[2][0][i] = temp[2][i][2];
		a[2][i][2] = temp[2][2][j];
		a[2][2][j] = temp[2][j][0];
		j--;
	}
}

void bottom(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// done

		a[1][2][i] = temp[4][2][j];
		a[2][2][i] = temp[1][2][i];
		a[3][2][i] = temp[2][2][i];
		a[4][2][i] = temp[3][2][i];

		//rotate face
		a[5][0][i] = temp[5][j][0];
		a[5][i][2] = temp[5][0][i];
		a[5][2][j] = temp[5][i][2];
		a[5][j][0] = temp[5][2][j];
		j--;
	}
}

void bottomI(string a[6][3][3])
{
	string temp[6][3][3];

	setTwoEqual(a, temp);

	int j = 2;
	for (int i = 0; i < 3; i++)
	{

		// done

		a[4][2][j] = temp[1][2][i];
		a[1][2][i] = temp[2][2][i];
		a[2][2][i] = temp[3][2][i];
		a[3][2][i] = temp[4][2][i];

		//rotate face
		a[5][j][0] = temp[5][0][i];
		a[5][0][i] = temp[5][i][2];
		a[5][i][2] = temp[5][2][j];
		a[5][2][j] = temp[5][j][0];
		j--;
	}
}

void randomize(string a[6][3][3])
{
	int rn = 0;
	srand(time(NULL));

	for (int i = 0; i < 20; i++)
	{
		rn = rand() % 11;
		switch (rn)
		{
		case 0:
			top(a);
			break;
		case 1:
			topI(a);
			break;
		case 2:
			front(a);
			break;
		case 3:
			frontI(a);
			break;
		case 4:
			right(a);
			break;
		case 5:
			rightI(a);
			break;
		case 6:
			back(a);
			break;
		case 7:
			backI(a);
			break;
		case 8:
			left(a);
			break;
		case 9:
			leftI(a);
			break;
		case 10:
			bottom(a);
			break;
		case 11:
			bottomI(a);
			break;
		}
	}
}

// white is top
// red is front
// blue is right
// orange is back
// green is left
// yellow is bottom

void operations(string a[6][3][3])
{
	right(a);
}

int main()
{
	string rubiks[6][3][3];
	createACube(rubiks);

	operations(rubiks);

	printCube(rubiks);

	system("pause");
	return 0;
}