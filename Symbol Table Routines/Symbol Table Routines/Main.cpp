#include "SymbolTable.h"
#include <iostream>

using namespace std;

int main()
{
	HashTable symbols;
	symbols.insert("Why");
	symbols.insert("Hello");
	symbols.insert("Where");
	symbols.insert("ComeOn");
	symbols.newScope();
	symbols.insert("Pop");
	symbols.insert("opP");
	symbols.closeScope();
	symbols.insert("yay!");

	symbols.print();
	symbols.find("Andrew");

	system("Pause");
	return 0;
}