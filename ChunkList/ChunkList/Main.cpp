#include <iostream>
#include <string>
#include "chunkList.h"

using namespace std;

int main()
{
	LinkedList<int> *list = new LinkedList<int>();
	
	for (int i = 0; i < 25; i++)
	{
		list->addElement((i * 502) % 115);
	}
	list->print();
	cout << "Int-list length: " << list->getSize() << "\n\n";

	for (int i = 0; i < 25; i += 2)
	{
		list->deleteElement((i * 502) % 115);
	}
	list->print();
	cout << "Deleted int-list length: " << list->getSize() << "\n\n";

	LinkedList<string> *list2 = new LinkedList<string>();
	list2->addElement("apples");
	list2->addElement("bananas");
	list2->addElement("kiwis");
	list2->addElement("mangos");
	list2->addElement("watermelon");
	list2->addElement("strawberries");
	list2->addElement("blueberries");
	list2->addElement("tangerines");

	cout << "Fullness of list: " << list2->isFull() << "\n\n";

	list2->addElement("pineapple");
	list2->addElement("guava");

	list2->print();

	cout << "Fruit-list length: " << list2->getSize() << "\n\n";

	list2->makeEmpty();

	cout << "Empty chunkList: ";
	list2->print();

	system("pause");
	return 0;
}