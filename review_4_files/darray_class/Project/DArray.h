#ifndef DARRAY_H
#define DARRAY_H

#include <iostream>
using namespace std;

class DArray
{
public:
    DArray( );
		//Initializes array to a capacity of 50.

    DArray(int newCapacity);
		//Initializes array to a given capacity.

    void addElement(int newElement);
		//Function to add a given element to the array.

	int getNumOfElements() const;
		//Function to return the number of elements in the array.

	void replaceElementAt(int newElement, int idx) const;
		//Function to replace an element at a given index.
		//We can make the function const because
		//  the member variable a is a pointer, it is NOT
		//  the array; therefore, because we are not changing
		//  the address that the pointer stores or any of
		//  the other member variables, the function can be
		//  a const function.
	
	bool compareArrays(const DArray& otherArray) const;
		//Function returns true if two arrays have the same 
		//elements in the same order, false otherwise.

	void printArray() const;
		//Function to print all elements in the array.
		//If the array is empty, outputs error message.
	
	~DArray( ); 
	//Destructor

private:
    int *a;					//will point to an array of integers
    int capacity;			//capacity of the array
    int numOfElements;		//total number of elements in the array

};

#endif