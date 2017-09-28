/*
	This program creates partially-filled 
	arrays of integers.
*/

#include "DArray.h"

#include <iostream>
using namespace std;

int main( )
{
	cout << "CLASS DARRAY\n\n";

	cout << "\n*** TEST: Default constructor / printArray ***\n\n";
	DArray a1;
	cout << "Array 1: "; 
	a1.printArray();

	cout << "\n*** TEST: Overloaded constructor / addElement / printArray ***\n\n";
	int capacityA2 = 10;
	DArray a2(capacityA2);
	for (int i = 0; i < 5; ++i)		// fill up only half array
		a2.addElement(i + 10);
	cout << "Array 2: ";
	a2.printArray();

	cout << "\n*** TEST: Fill up array with more elements  ***\n\n";
	int numOfElementsA2 = a2.getNumOfElements();
	for (int i = numOfElementsA2; i < capacityA2; ++i)
		a2.addElement(i + 10);
	cout << "Array 2 is now: ";
	a2.printArray();

	cout << "\n*** TEST: replaceElementAt (index 4)  ***\n\n";
	a2.replaceElementAt(100, 4);
	cout << "Array 2 is now: ";
	a2.printArray();

	cout << "\n*** TEST: compareArrays  ***\n\n";

	cout << "Different number of elements...\n";
	DArray arr1(10);
	arr1.addElement(10);
	arr1.addElement(11);
	arr1.addElement(12);
	arr1.addElement(13);
	arr1.addElement(14);
	DArray arr2(10);
	arr2.addElement(10);
	arr2.addElement(11);
	arr2.addElement(12);
	arr2.addElement(13);
	cout << "arr1: ";
	arr1.printArray();
	cout << "arr2: ";
	arr2.printArray();
	if (arr1.compareArrays(arr2))
		cout << "    Arrays are the same." << endl;
	else
		cout << "    Arrays are different." << endl;

	cout << "\nDifferent first element...\n";
	DArray arr3(10);
	arr3.addElement(500);
	arr3.addElement(11);
	arr3.addElement(12);
	arr3.addElement(13);
	arr3.addElement(14);
	cout << "arr1: ";
	arr1.printArray();
	cout << "arr3: ";
	arr3.printArray();
	if (arr1.compareArrays(arr3))
		cout << "    Arrays are the same." << endl;
	else
		cout << "    Arrays are different." << endl;

	cout << "\nDifferent last element...\n";
	arr3.replaceElementAt(10, 0);
	arr3.replaceElementAt(500, arr3.getNumOfElements() - 1);
	cout << "arr1: ";
	arr1.printArray();
	cout << "arr3: ";
	arr3.printArray();
	if (arr1.compareArrays(arr3))
		cout << "    Arrays are the same." << endl;
	else
		cout << "    Arrays are different." << endl;

	cout << "\nDifferent middle element...\n";
	arr3.replaceElementAt(14, arr3.getNumOfElements() - 1);
	arr3.replaceElementAt(500, arr3.getNumOfElements() / 2);
	cout << "arr1: ";
	arr1.printArray();
	cout << "arr3: ";
	arr3.printArray();
	if (arr1.compareArrays(arr3))
		cout << "    Arrays are the same." << endl;
	else
		cout << "    Arrays are different." << endl;

	cout << "\nSame elements...\n";
	arr3.replaceElementAt(12, arr3.getNumOfElements() / 2);
	cout << "arr1: ";
	arr1.printArray();
	cout << "arr3: ";
	arr3.printArray();
	if (arr1.compareArrays(arr3))
		cout << "    Arrays are the same." << endl;
	else
		cout << "    Arrays are different." << endl;

	cout << endl;
	system("Pause");
    return 0;
}

