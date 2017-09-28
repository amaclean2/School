/*
	Maclean, Andrew
	May 6th, 2016
	Lab 8
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void fill(string db[20][5], int& counter)
{
	string id, firstName, lastName, userName, email;

	cout << "Please create a user\n" << endl;
	id = to_string(counter + 1);
	cout << "First Name:" << endl;
	getline(cin, firstName);
	cout << "Last Name:" << endl;
	getline(cin, lastName);
	cout << "User Name:" << endl;
	getline(cin, userName);
	cout << "Email:" << endl;
	getline(cin, email);
	db[counter][0] = id;
	db[counter][1] = firstName;
	db[counter][2] = lastName;
	db[counter][3] = userName;
	db[counter][4] = email;
	counter++;
}

void update(string db[20][5], const int& counter)
{
	string un;
	int i = 0;
	bool correct = false;
	while (!correct)
	{
		cout << "Select a user, by username, to update:" << endl;
		getline(cin, un);
		i = 0;
		while (db[i][3] != un && i < counter)
			i++;
		if (db[i][3] == un)
		{
			correct = true;
			cout << "Press Enter to skip any fields you do not want to update." << endl;
			string firstName, lastName, userName, email;

			cout << "First Name:" << endl;
			getline(cin, firstName);
			cout << "Last Name:" << endl;
			getline(cin, lastName);
			cout << "User Name:" << endl;
			getline(cin, userName);
			cout << "Email:" << endl;
			getline(cin, email);
			if (firstName != "")
				db[i][1] = firstName;
			if (lastName != "")
				db[i][2] = lastName;
			if (userName != "")
				db[i][3] = userName;
			if (email != "")
				db[i][4] = email;
		}
		else
			cerr << "That user doesn't exist" << endl;
	}
}

void print(const string db[20][5], const int& counter)
{
	cout << setw(2) << "ID" << "  |  ";
	cout << setw(20) << "First Name" << "  |  ";
	cout << setw(20) << "Last Name" << "  |  ";
	cout << setw(20) << "User Name" << "  |  ";
	cout << setw(20) << "Email" << "  |  ";
	cout << endl;

	for (int i = 0; i < counter; i++)
	{
		cout << setw(2) << db[i][0] << "  |  ";
		cout << setw(20) << db[i][1] << "  |  ";
		cout << setw(20) << db[i][2] << "  |  ";
		cout << setw(20) << db[i][3] << "  |  ";
		cout << setw(20) << db[i][4] << "  |  ";
		cout << endl;
	}
}

int main()
{
	cout << "Users\n\n";
	cout << "This is a program that stores usernames, emails, and names of users." << endl;
	cout << "Please follow the instructions to continue.\n" << endl;
	string db[20][5];
	int counter = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 5; j++)
			db[i][j] = "";
	}

	string choice = "0";
	
	while (choice != "4" && counter < 20)
	{
		if (counter > 0)
		{
			do
			{
				system("pause");
				system("cls");
				cout << "What would you like to do?" << endl;
				cout << "  1 - add an entry" << endl;
				cout << "  2 - update an entry" << endl;
				cout << "  3 - view all entries" << endl;
				cout << "  4 - exit" << endl;

				getline(cin, choice);

				if (choice == "1")
					fill(db, counter);
				else if (choice == "2")
					update(db, counter);
				else if (choice == "3")
					print(db, counter);
				else if (choice == "4")
					cout << "";
				else
					cout << "I didn't get that, can you try again?" << endl;
			} while (choice != "4");
		}
		else
			fill(db, counter);
	}

	cout << "Thank You!" << endl;
	system("pause");
	return 0;
}