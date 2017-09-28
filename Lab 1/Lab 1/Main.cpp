/*
	Andrew Maclean
	February 24, 2016
	Lab One
*/

#include <iostream>
#include <string>
using namespace std;

bool checkEntry(const string& entry, const string quals[4][3])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (entry == quals[i][j])
				return true;
		}
	}
	return false;
}

int level(const string& s, const string quals[4][3])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (s == quals[i][j])
				return (i + 1);
		}
	}
}

void printQuals(const string quals[4][3])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << quals[i][j] << endl;
		cout << endl;
	}
}

void statement()
{
	cout << "Please enter your qualifications from the list. You have to enter exactly an item from the list. " <<
		"It is ok if you misstype you can enter your entry again." << endl << "You have ten spaces for entries." << endl << "You may press enter at any time you are finished" << endl;
}

int main()
{
	cout << "Applicant Qualifications" << endl << endl;
	string quals[4][3] = {
		{
			"Bachelor's Degree or higher in Computer Science",
			"Has experience with Javascript, Node, and HTML5",
			"Has experience with at least two of C++, Java, and C#"
		},
		{
			"Bachelors Degree or higher in Computer Scinece or Mathematics",
			"Has experience with at last two of Javascript, Node, and HTML5",
			"Has experience with at least one of C++, Java, and C#"
		},
		{
			"No Degree in Computer Science or Mathematics, but at least 3 years of related experience",
			"Has experience with one or more of Javascript, Mode, or HTML5",
			"Has experinece with one or more of C++, Java, or C#"
		},
		{
			"No Degree in Computer Science or Mathematics, or less than 3 years of related experience",
			"No experience with Javascript, Node, or HTML5",
			"No experience with C++, Java, or C#"
		},
	};
	printQuals(quals);
	statement();

	string applicantsQuals[10];
	for (int i = 0; i < 10; i++)
		applicantsQuals[i] = "";

	string entry = "a";

	int i = 0;
	while (i < 10 && entry != "")
	{
		if (i == 9)
			cout << "Last entry..." << endl;
		do
		{
			cout << "Please enter a requirement provided." << endl;
			getline(cin, entry);
			if (entry != "" && checkEntry(entry, quals))
				applicantsQuals[i] = entry;
		} while (entry != "" && !checkEntry(entry, quals));
		i++;
	}

	int VC = 0;
	int AC = 0;
	int MC = 0;
	int NC = 0;
	i = 0;
	while (applicantsQuals[i] != "" && i < 10)
	{
		string q = applicantsQuals[i];
		if (level(q, quals) == 1)
			VC++;
		else if (level(q, quals) == 2)
			AC++;
		else if (level(q, quals) == 3)
			MC++;
		else
			NC++;
		i++;
	}
	if (VC == 3)
		cout << "You are very qualified" << endl;
	else if (AC == 3)
		cout << "You are Adequately qualified" << endl;
	else if (MC == 3)
		cout << "You are Minimally qualified" << endl;
	else
		cout << "You are not qualified" << endl;

	cout << "Thank You" << endl;

	system("pause");
	return 0;
}