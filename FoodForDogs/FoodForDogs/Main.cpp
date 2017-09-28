#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void read(string gfd[28], string bfd[20])
{
	string dog;
	int i = 0;

	ifstream dogs("GoodForDogs.txt");
	if (dogs.is_open())
	{
		while (getline(dogs, dog))
		{
			gfd[i] = dog;
			i++;
		}
		dogs.close();
	}
	else
		cerr << "The file could not be opened." << endl;

	i = 0;
	ifstream dogs2("BadForDogs.txt");
	if (dogs2.is_open())
	{
		while (getline(dogs2, dog))
		{
			bfd[i] = dog;
			i++;
		}
		dogs2.close();
	}
	else
		cerr << "The file could not be opened." << endl;
}

void enter(string entry[6])
{
	cout << "Please enter up to 6 foods to see if they are acceptable for dogs to eat." << endl;
	string line = "";
	for (int i = 0; i < 6; i++)
		entry[i] = line;
	int i = 0;
	do
	{
		getline(cin, line);
		entry[i] = line;
		i++;
	} while (line != "" && i < 6);
}

string check(const string gfd[28], const string bfd[20], const string& food)
{
	string c = "";
	for (int i = 0; i < 28; i++)
	{
		if (food == gfd[i])
		{
			c = gfd[i];
			return "good";
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (food == bfd[i])
		{
			c = bfd[i];
			return "bad";
		}
	}
	return c;
}

void print(const string fAndG[6], const string fAndB[6], const string fAndNone[6])
{
	cout << "Food that's good for dogs" << endl;
	int i = 0;
	while (i < 6 && fAndG[i] != "")
	{
		cout << fAndG[i] << endl;
		i++;
	}
	cout << endl;
	i = 0;
	cout << "\nFood that's bad for dogs" << endl;
	while (i < 6 && fAndB[i] != "")
	{
		cout << fAndB[i] << endl;
		i++;
	}
	cout << endl;
	i = 0;
	cout << "\nFood that isn't on either list" << endl;
	while (i < 6 && fAndNone[i] != "")
	{
		cout << fAndNone[i] << endl;
		i++;
	}
}

int main()
{
	cout << "Food For Dogs" << endl << endl;
	cout << "This program takes foods that you enter and checks to see if they are ok for dogs to eat" << endl << endl;
	string g[28], b[20], f[6];
	string fAndG[6], fAndB[6], fAndNone[6];
	char question = 'n';

	read(g, b);
	do
	{
		if (question == 'y')
			cin.ignore();
		enter(f);

		for (int i = 0; i < 6; i++)
		{
			fAndG[i] = "";
			fAndB[i] = "";
			fAndNone[i] = "";
		}
		int gf = 0;
		int bf = 0;
		int nf = 0;
		int a = 0;
		while (f[a] != "" && a < 6)
		{
			if (check(g, b, f[a]) != "")
			{
				if (check(g, b, f[a]) == "good")
				{
					fAndG[gf] = f[a];
					gf++;
				}
				else
				{
					fAndB[bf] = f[a];
					bf++;
				}
			}
			else
			{
				fAndNone[nf] = f[a];
				nf++;
			}
			a++;
		}

		print(fAndG, fAndB, fAndNone);

		cout << "Please enter y to continue or n to quit";
		cin >> question;
	} while (question == 'y');
	



	cout << endl << "Thank You" << endl;
	system("pause");
	return 0;
}
