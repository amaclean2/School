/*
	Andrew Maclean
	CS4110
	January 26, 2017

	Algol Scanner for Baby Algol
*/

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

string getToken(string& line, queue<int>& tokens)
{
	struct token {
		string tokenName;
		int tokenNumber;
	};

	//array of lexemes
	token lexemes[] = { {"(", 14}, {")", 15}, {";", 16}, {".", 18}, {"*", 5}, {"+", 4}, {"-", 4}, {"/", 5}, {"<", 6}, {">", 6}, {"=", 6}, {"!", 17},{ ":=", 6 }, { "!=", 6 } };
	//array of keys
	token keys[] = { {"BEGIN", 7},  {"IF", 9}, {"WHILE", 11}, {"INTEGER", 3}, {"TRUE", 2}, {"OR", 4}, {"READ", 13}, {"END", 8}, {"THEN", 10}, {"DO", 3}, {"STRING", 3},
	{"FALSE", 2}, {"AND", 5}, {"WRITE", 13}, {"LOGICAL", 3}, {"DIV", 5}, {"REAL", 16}, {"REM", 5}, {"WRITELN", 13} };
	string check = ""; // store for words or numbers
	string errors = ""; // store for errors
	int lSize = 14; // length of lexemes array
	int kSize = 19; // length of keys array
	bool found;
	int size = line.size();
	int j;
	int up; // convert string to upper int counter
	char c;
	for (int i = 0; i < size; i++) //goes through each character of the line
	{
		check = "";
		j = 0;
		//checks for identifiers starting with a letter or numbers
		if (isalpha(line[i]))
		{
			check.push_back(line[i]);
			i++;
			//check for sequential digits/letters
			while (isalnum(line[i]))
			{
				check.push_back(line[i]);
				i++;
			}
			//check for an end
			if (!isalnum(line[i]))
			{
				up = 0;
				while (check[up])
				{
					c = check[up];
					if(islower(c)) c = (toupper(c));
					up++;
				}
				j = 0;
				//check for comments
				if (check == "COMMENT")
					i = size;
				else
				{
					//check for keywords
					while (j < (kSize - 1) && check != keys[j].tokenName)
						j++;
					if (check == keys[j].tokenName)
						tokens.push(keys[j].tokenNumber);
					//classify as identifier
					else
						tokens.push(1);
				}
			}
			i--;
		}
		if (isdigit(line[i]))
		{
			check.push_back(line[i]);
			i++;
			while (isdigit(line[i]))
			{
				check.push_back(line[i]);
				i++;
			}
			if (!isdigit(line[i]))
			{
				tokens.push(2);
			}
			i--;
		}
		//check for non-whitespace variables
		if (isalnum(line[i])) i++;
		else if (line[i] != ' ' && i < size)
		{
			found = false;
			//check for multi-character lexemes
			if (line[i] == ':' && line[i + 1] == '=')
			{
				tokens.push(6);
				found = true;
			}
			else if (line[i] == '!' && line[i + 1] == '=')
			{
				tokens.push(6);
				found = true;
			}
			//check for all other lexemes
			else
			{
				while (j < (lSize - 2) && found == false)
				{
					if (line[i] == lexemes[j].tokenName[0])
					{
						tokens.push(lexemes[j].tokenNumber);
						found = true;
					}
					else if (line[i] == '	')
					{
						tokens.push(1);
						found = true;
					}
					j++;
				}
			}
			//check for illegal characters
			if (found == false)
			{
				string message = "illegal character ";
				message.push_back(line[i]);
				message.push_back(' ');
				errors.append(message);
			}
			
		}
	}

	if (errors.size() > 0)
		errors.insert(0, "        err: ");
	return errors;
}

void readFile()
{
	string line;
	string err = "";
	//reads the text file
	ifstream input("inputFile.txt");
	//opens a listing file
	ofstream output;
	output.open("outputFile.txt");
	queue<int> tokens;
	int i = 1;
	//reads the input file line by line
	if (input.is_open())
	{
		while (getline(input, line))
		{
			err = getToken(line, tokens);
			output << i << ":  " << line << err << endl;
			i++;
		}
		input.close();
		output.close();
	}

	else cout << "Unable to open" << endl;
}

int main()
{
	readFile();
	return 0;
}