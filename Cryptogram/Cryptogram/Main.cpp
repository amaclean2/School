#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

void encrypt(string fileName);

void decrypt(string fileName);

void key(string& lin, int size, char enc);

void menu();

int main()
{
	menu();	
	
	cout << endl;
	system("pause");
	return 0;
}

void encrypt(string fileName)
{
	ifstream testFile;
	ofstream inFile;
	testFile.open(fileName);

	string line;
	int size;
	if (testFile.is_open())
	{
		string eFile = "encrypted" + fileName;
		inFile.open(eFile);
		while (getline(testFile, line))
		{
			size = line.size();
			key(line, size, 'e');
			inFile << line << endl;
		}
		testFile.close();

		cout << "Your encrypted file is " << eFile << endl;
	}
	else cout << "Can't open the file." << endl;
}

void decrypt(string fileName)
{
	ifstream testFile;
	ofstream inFile;
	testFile.open(fileName);


	string line;
	int size;
	if (testFile.is_open())
	{
		string eFile = fileName.erase(0, 9);
		inFile.open(eFile);

		while (getline(testFile, line))
		{
			size = line.size();
			key(line, size, 'd');
			inFile << line << endl;
		}
		testFile.close();

		cout << "Your decrypted file is " << eFile << endl;
	}
	else cout << "Can't open the file." << endl;
}

void key(string& lin, int size, char enc)
{
	if (enc == 'e')
	{
		for (int i = 0; i < size; i++)
			lin[i] = lin[i] + 5;
	}
	else
	{
		for (int i = 0; i < size; i++)
			lin[i] = lin[i] - 5;
	}
}

void menu()
{
	string e;
	do
	{
		cout << "Would you like to encrypt or decrypt a file?" << endl;
		getline(cin, e);
		string file;
		if (e == "encrypt")
		{
			cout << "Enter the name of a text file to encrypt." << endl;
			getline(cin, file);
			file = file + ".txt";
			encrypt(file);
		}

		else if (e == "decrypt")
		{
			cout << "Enter the name of a text file to decrypt." << endl;
			getline(cin, file);
			file = file + ".txt";
			if (file.substr(0, 4) != "encr")
				cerr << "Your file is not encrypted." << endl;
			else
				decrypt(file);
		}
	} while (e == "encrypt" || e == "decrypt");
}