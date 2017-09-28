#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

class Scanner
{
public:
	Scanner()
	{
		line = "";
		lineNo = 0;
	}
	string pushTokens(string& lineI, int lineNumb, queue<token>& tokens, ofstream& scPa)
	{
		struct token
		{
			string tokenName;
			int lineNo;
			int tokenNumber;
		};
		struct lex
		{
			string tokenName;
			int tokenNumber;
		};
		//array of lexemes
		lex lexemes[] = { { "(", 14 },{ ")", 15 },{ ";", 16 },{ ".", 18 },{ "*", 5 },{ "+", 4 },{ "-", 4 },{ "/", 5 },{ "<", 6 },{ ">", 6 },{ "=", 6 },{ "!", 17 },{ ":=", 19 },{ "!=", 6 } };
		//array of keys
		lex keys[] = { { "BEGIN", 7 },{ "IF", 9 },{ "WHILE", 11 },{ "INTEGER", 3 },{ "TRUE", 2 },{ "OR", 4 },{ "READ", 13 },{ "END", 8 },{ "THEN", 10 },{ "DO", 12 },{ "STRING", 3 },
		{ "FALSE", 2 },{ "AND", 5 },{ "WRITE", 13 },{ "LOGICAL", 3 },{ "DIV", 5 },{ "REAL", 16 },{ "REM", 5 },{ "WRITELN", 13 } };
		string check = ""; // store for words or numbers
		string strings = ""; // stores any possible strings
		string errors = ""; // store for errors
		int lSize = 14; // length of lexemes array
		int kSize = 19; // length of keys array
		bool found;
		int size = line.size();
		int j;
		int up; // convert string to upper int counter
		char c;
		int i = 0;
		while (i < size) //goes through each character of the line
		{
			check = "";
			j = 0;
			if (line[i] == ' ' || line[i] == '	')
				i++;
			//checks any strings starting and ending with "
			else if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
				{
					strings.push_back(line[i]);
					i++;
				}
				i++;
				tokens.push({ strings, lineNo, 2 });
				scPa << strings << 2 << ", ";
			}
			// checks for identifiers or keywords
			else if (isalpha(line[i]))
			{
				check.push_back(line[i]);
				i++;
				//check for sequential digits/letters
				while (isalnum(line[i]))
				{
					check.push_back(line[i]);
					i++;
				}
				up = 0;
				while (check[up])
				{
					c = check[up];
					if (islower(c))
					{
						c = toupper(c);
						check[up] = c;
					}
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
					{
						tokens.push({ keys[j].tokenName, lineNo, keys[j].tokenNumber });
						scPa << check << keys[j].tokenNumber << ", ";
					}
					//classify as identifier
					else
					{
						tokens.push({ check, lineNo, 1 });
						scPa << check << 1 << ", ";
					}
				}
			}
			// checks for numbers
			else if (isdigit(line[i]))
			{
				check.push_back(line[i]);
				i++;
				while (isdigit(line[i]))
				{
					check.push_back(line[i]);
					i++;
				}
				tokens.push({ check, lineNo, 2 });
				scPa << check << 2 << ", ";
			}
			// checks for other lexemes
			else
			{
				found = false;
				//check for multi-character lexemes
				if (line[i] == ':' && line[i + 1] == '=')
				{
					tokens.push({ ":=", lineNo, 19 });
					scPa << ":=" << 19 << ", ";
					found = true;
					i += 2;
				}
				else if (line[i] == '!' && line[i + 1] == '=')
				{
					tokens.push({ "!=", lineNo, 6 });
					scPa << "!=" << 6 << ", ";
					found = true;
					i += 2;
				}
				//check for all other lexemes
				else
				{
					while (j < (lSize - 2) && found == false)
					{
						if (line[i] == lexemes[j].tokenName[0])
						{
							tokens.push({ lexemes[j].tokenName, lineNo, lexemes[j].tokenNumber });
							scPa << line[i] << lexemes[j].tokenNumber << ", ";
							found = true;
						}
						j++;
					}
					i++;
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

private:
	string line;
	int lineNo;
};

#endif