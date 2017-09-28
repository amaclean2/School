#include <iostream>
#include <string>
using namespace std;

int hashFun(const string& album)
{
	int len = album.length();
	int sum = 0;
	int letter, ha;
	for (int i = 0; i < len; i++)
	{
		letter = (int)album[i];
		sum += letter;
	}
	ha = sum % 6;
	return ha;
}

void print(const string* albums)
{
	for (int i = 0; i < 6; i++)
	{
		if (albums[i] == "")
			cout << "No Album" << " | ";
		else
			cout << albums[i] << " | ";
	}
	cout << endl;
}

int main()
{
	////////////bio.......
	cout << "You can enter up to 6 albums in this table and it will store them for you. \nOnce you have entered your albums, ";
	cout << "you can search them by following the \nsteps described." << endl;
	////////////

	string album = "";
	string storage[] = { "", "", "", "", "", "" };
	bool complete = false;
	while (!complete)
	{
		cout << "Enter an album name or a space to end" << endl;
		getline(cin, album);
		if (album != " ")
		{
			if (storage[hashFun(album)] == "")
				storage[hashFun(album)] = album;
			else
			{
				int a = hashFun(album);
				int i = 0;
				while (storage[a] != "" && i < 6)
				{
					a++;
					if (a == 6)
						a = 0;
					i++;
				}
				if (i < 6)
					storage[a] = album;
				else
				{
					cerr << "There is no more room" << endl;
					complete = true;
				}
			}
		}
		else
		{
			cout << "Are you sure you are done? Enter y or n." << endl;
			char a;
			do
			{
				cin >> a;
				if (a == 'y')
					complete = true;
				else if (a == 'n')
					complete = false;
				else
					cerr << "That is not a valid answer." << endl;
			} while (!(a == 'y' || a == 'n'));
		}
	}
	print(storage);
	bool contin = true;
	while (contin != false)
	{
		string album;
		cout << "What album would you like to search for?" << endl;
		getline(cin, album);

		int a = hashFun(album);
		int i = 0;
		while (storage[a] != "album" && i < 6)
		{
			a++;
			if (a == 6)
				a = 0;
			i++;
		}
		if (i < 6)
		{
			cout << "The album was found" << endl;
			cout << i << " elements has to be searched." << endl;
		}
		else
			cerr << "The album wasn't found" << endl;


		cout << "Would you like to searh another? Enter y or n." << endl;
		char ab;
		do
		{
			cin >> ab;
			if (ab == 'y')
				contin = true;
			else if (ab == 'n')
				contin = false;
			else
				cerr << "That is not a valid answer." << endl;
		} while (!(ab == 'y' || ab == 'n'));
	}


	cout <<endl << "Thank You, and Good Bye!" << endl;
	system("pause");
	return 0;
}