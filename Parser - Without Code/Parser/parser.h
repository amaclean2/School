#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "SymbolTable.h"

using namespace std;

struct token
{
	string tokenName;
	int lineNo;
	int tokenNumber;
};

class Parser
{
public:
	Parser(queue<token> tokenList)
	{
		tokens = tokenList;
		identifiers = new HashTable();
		program();
		currentAddr = 0;
	}

	// makes sure there is at least one token left to pop
	void countCheck()
	{
		if (tokens.size() == 0)
		{
			cerr << "\nNot enough tokens" << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
	}

	//does prints the rule number somewhere
	void print(int tok)
	{
		cout << tok << " ";
	}
	//idref -> IDTOK
	void idref()
	{
		print(31);
		if (tokens.front().tokenNumber != 1) // missing token error
			cerr << "\nMissing identifier on line: " << tokens.front().lineNo << endl;
		else
		{
			if(identifiers->find(tokens.front().tokenName) != "Not Found")
				tokens.pop(); //pop IDTOK
			else
			{
				cerr << "\nError undeclared identifier " << tokens.front().tokenName << " on line: " << tokens.front().lineNo << endl;
				tokens.pop();
			}
		}
		countCheck();
	}

	//factor -> NOTTOK factor | idref | LITTOK | '(' expression ')'
	void factor()
	{
		// token 17 is NOTTOK
		if (tokens.front().tokenNumber == 17)
		{
			print(27);
			tokens.pop(); //pop NOTTOK
			factor();
		}
		//token 1 is ID
		else if (tokens.front().tokenNumber == 1)
		{
			print(28);
			idref();
		}
		//token 2 is LITERAL
		else if (tokens.front().tokenNumber == 2)
		{
			print(29);
			tokens.pop(); //pop LITTOK
			countCheck();
		}
		//token 14 is (
		else if (tokens.front().tokenNumber == 14)
		{
			print(30);

			tokens.pop(); //pop (

			countCheck();
			expression();
			
			//token 15 is )
			if (tokens.front().tokenNumber != 15) // missing token error
				cerr << "\nExpected \')\' on line: " << tokens.front().lineNo << endl;
			else
				tokens.pop(); //pop )
		}
		countCheck();

	}

	//factorprime -> RELOPTOK factor | empty
	void factorprime()
	{
		//token 6 is RELOPTOK
		if (tokens.front().tokenNumber == 6)
		{
			print(25);

			tokens.pop(); //pop RELOPTOK

			countCheck();
			factor();
		}
		else
			print(26);
	}

	//relfactor -> factor factorprime
	void relfactor()
	{
		print(24);
		factor();
		factorprime();
	}

	//termprime -> MULOPTOK relfactor termprime | empty
	void termprime()
	{
		//token 5 is NULLOPTOK
		if (tokens.front().tokenNumber == 5)
		{
			print(22);
			tokens.pop(); //pop MULOPTOK
			countCheck();
			relfactor();
			termprime();
		}
		else
			print(23);
	}
	//term -> relfactor termprime
	void term()
	{
		print(21);
		relfactor();
		termprime();
	}

	//expprime -> ADDOPTOK term expprime | empty
	void expprime()
	{
		//token 4 is ADDOPTOK
		if (tokens.front().tokenNumber == 4)
		{
			print(19);
			tokens.pop(); //pop ADDOPTOK
			countCheck();
			term();
			expprime();
		}
		else
			print(20);
	}

	//expression -> term expprime
	void expression()
	{
		print(18);
		term();
		expprime();
	}

	//iostat -> READTOK '(' idref ')' | WRITETOK '(' expression ')'
	void iostat()
	{
		string key;

		key = tokens.front().tokenName;
		tokens.pop(); //pop READTOK or WRITETOK
		countCheck();

		if (tokens.front().tokenNumber != 14) // missing token error, (
			cerr << "\nExpected \'(\' in iostat on line: " << tokens.front().lineNo << endl;
		else
			tokens.pop(); //pop open parenthesis

		countCheck();

		if (key == "READ")
		{
			print(16);
			idref();
		}
		else
		{
			print(17);
			expression();
		}

		if (tokens.front().tokenNumber != 15) // missing token error on )
			cerr << "\nExpected \')\' in iostat on line: " << tokens.front().lineNo << endl;
		else
			tokens.pop(); //pop closed parentheis

		countCheck();
	}

	//loopst -> WHILETOK expression DOTOK statmt
	void loopst()
	{
		print(15);
		// WHILE is token 11
		tokens.pop(); //pop WHILETOK
		expression();
		//DO is token 12
		if (tokens.front().tokenNumber != 12) // missing token error
			cerr << "\nMissing \"Do\" token on line: " << tokens.front().lineNo << endl;
		else
			tokens.pop(); //pop DOTOK
		statmt();
	}

	//ifstat -> IFTOK expression THENTOK statmt
	void ifstat()
	{
		print(14);

		tokens.pop(); //pop IFTOK

		countCheck();
		expression();

		if (tokens.front().tokenNumber != 10) // missing token error, token 10 is THEN
			cerr << "\nExpected \"then\" token, got " << tokens.front().tokenName  << " on line: " << tokens.front().lineNo << endl;
		else
			tokens.pop(); //pop THENTOK

		countCheck();
		statmt();
	}

	//assstat -> idref ASTOK expression
	void assstat()
	{
		print(13);
		//as long as it doesn't find the identifier...
		if (identifiers->find(tokens.front().tokenName) != "Not Found")
			idref();
		//give an error otherwise
		else
		{
			cerr << "\nIdentifier " << tokens.front().tokenName << " was not found on line: " << tokens.front().lineNo << endl;
			tokens.pop();
		}
		if (tokens.front().tokenNumber != 19) // missing token error
			cerr << "\nExpected :=, got " << tokens.front().tokenName << " on line: " << tokens.front().lineNo << endl;
		else
			tokens.pop();
		countCheck();
		expression();
	}

	//stmt -> decl | ifstat | assstat | blockst | loopst | iostat | empty
	void statmt()
	{
		if (tokens.front().tokenNumber == 3)
		{
			print(6);
			decl();
		}
		else if (tokens.front().tokenNumber == 9)
		{
			print(7);
			ifstat();
		}
		else if (tokens.front().tokenNumber == 1)
		{
			print(8);
			assstat();
		}
		else if (tokens.front().tokenNumber == 7)
		{
			print(9);
			blockst();
		}
		else if (tokens.front().tokenNumber == 11)
		{
			print(10);
			loopst();
		}
		else if (tokens.front().tokenNumber == 13)
		{
			print(11);
			iostat();
		}
		else
			print(12);
	}

	//decl -> BASICTYPETOK IDTOK
	void decl()
	{
		print(5);
		string type = tokens.front().tokenName;
		tokens.pop(); //pop TYPETOK

		countCheck();

		if (tokens.front().tokenNumber != 1) // missing token error IDENT
			cerr << "\nMissing identifier on line: " << tokens.front().lineNo << endl;
		else
		{
			if (identifiers->find(tokens.front().tokenName) == "Not Found")
			{
				Data inserted = { type, tokens.front().tokenName, currentAddr};
				identifiers->insert(inserted); //pop IDTOK
				tokens.pop();
			}
			//doesn't make two identifiers
			else
			{
				cerr << "\nIdentifier already exists, on line: " << tokens.front().lineNo << endl;
				tokens.pop();
			}
		}
		countCheck();
		currentAddr -= 4;
	}

	//stats -> statmt ';' stats | empty
	void stats()
	{
		if (tokens.front().tokenNumber != 8)
		{
			print(3);
			statmt();
			if (tokens.front().tokenNumber != 16) // missing token error
				cerr << "\nMissing \';\' on line: " << tokens.front().lineNo << endl;
			else //pop ;
			{
				tokens.pop();
				countCheck();
				stats();
			}
		}
		else
			print(4);
	}

	//blockst -> BEGINTOK stats ENDTOK
	void blockst()
	{
		print(2);
		if (tokens.front().tokenNumber != 7) // missing token error
			cerr << "\nMissing begin token on line: " << tokens.front().lineNo << endl;
		else
		{
			//pop BEGIN
			tokens.pop();
			identifiers->newScope();
		}
		countCheck(); // makes sure that the token count is greater than zero
		stats();
		if (tokens.front().tokenNumber != 8) // missing token error
			cerr << "\nMissing end token on line: " << tokens.front().lineNo << endl;
		else
		{
			//pop END
			tokens.pop();
			identifiers->closeScope();
		}
		countCheck();
	}

	//program -> blockst '.'
	void program()
	{
		print(1);
		blockst();
		if (tokens.front().tokenNumber != 18) // missing token error
			cerr << "\nNo end of program token\n";
		cout << "\n";
		identifiers->print();
	}

private:
		queue<token> tokens;
		HashTable* identifiers;
		int currentAddr;
};

#endif