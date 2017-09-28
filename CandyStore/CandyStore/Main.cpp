/*
	Andrew Maclean
	Lab 00
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	string names[2][5];
	int quantity[5];
	cout << "This is a program that takes the names, candy, and quantity" << endl;
	cout << "sold of fifteen customers to a candy shop and outputs the" << endl;
	cout << "information in a table. The user has to enter each" << endl;
	cout << "field manually and once fifteen customers are filled" << endl;
	cout << "out then the table will display." << endl;
	system("pause");
	system("cls");
	cout << "Please enter the name of fifteen customers and the information following.\n";
	for (int i = 0; i < 5; i++)
	{
		cout << "Customer's name: ";
		cin >> names[0][i];
		cout << "Customer's product: ";
		cin >> names[1][i];
		cout << "Quantity sold: ";
		cin >> quantity[i];
		system("cls");
	}
	int b, a = 0;
	while (a < 3)
	{
		b = 0;
		while (b < 5)
		{
			if (a < 2)
			{
				cout << setw(10);
				cout << names[a][b];
			}
			else
			{
				cout << setw(10);
				cout << quantity[b];
			}
			cout << "  |  ";
			b++;
		}
		cout << endl;
		a++;
	}

	system("pause");
	return 0;
}