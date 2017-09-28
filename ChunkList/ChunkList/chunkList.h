#ifndef CHUNKLIST_H
#define CHUNKLIST_H

#include <iostream>
#include <iomanip>

const int ARR_CAPACITY = 8;

template <class T>
class Node
{
public:
	Node() { arr = new T[0]; ptrToNext = NULL; size = 0;}
	Node(Node *newPtrToNext) { arr = new T[ARR_CAPACITY]; ptrToNext = newPtrToNext; size = 0; }
	Node<T> *getNext() const { return ptrToNext; }
	int getSize() const { return size; }
	T* getData() const { return arr; }
	void setNext(Node* newPtrToNext) { ptrToNext = newPtrToNext; }
	void setSize(int newSize) { size = newSize; }
	bool isFull() { return (size == ARR_CAPACITY); }

	// destructor
	~Node() {}

private:
	T *arr;
	Node<T> *ptrToNext;
	int size;
};

template <class T>
class LinkedList
{
public:
	LinkedList()
	{
		ptrToFirst = NULL;
		ptrToTail = NULL;
		cap = 0;
		size = 0;
	}

	void addArray()
	{
		Node<T>* item = new Node<T>(NULL);
		Node<T> *node = ptrToFirst;
		if (node == NULL)
		{
			ptrToFirst = item;
			ptrToTail = item;
		}
		else
		{
			while (node->getNext() != NULL)
				node = node->getNext();

			node->setNext(item);
			ptrToTail = item;
		}
		cap += ARR_CAPACITY;
	}

	void addElement(T element)
	{
		Node<T> *node = ptrToFirst;

		if (node == NULL || isFull())
		{
			addArray();
			addElement(element);
		}
		else
		{
			while (node->getSize() == ARR_CAPACITY)
				node = node->getNext();

			node->getData()[node->getSize()] = element;
			node->setSize(node->getSize() + 1);
			size++;
		}
	}

	void addInOrder(T element)
	{
		Node<T> *node = ptrToFirst;
		int temp, i, prevTemp;
		if (node == NULL)
			cerr << "no arrays have been added" << endl;
		else if (isFull())
			cerr << "all arrays are full" << endl;
		else
		{
			if (node->getSize() == 0)
			{
				node->getData()[0] = element;
				node->setSize(node->getSize() + 1);
			}
			else
			{
				i = 0;
				if (element == 34)
					cout << "tada";
				while (node != NULL && node->getData()[i] < element && i < node->getSize())
				{
					if (i == ARR_CAPACITY - 1)
					{
						i = 0;
						node = node->getNext();
					}
					else
						i++;
				}

				if (!node->isFull())
				{
					if (i == node->getSize())
						node->getData()[node->getSize()] = element;
					else
					{
						for (int j = node->getSize(); j > i; j--)
							node->getData()[j] = node->getData()[j - 1];
						node->getData()[i] = element;
					}

					node->setSize(node->getSize() + 1);
				}
				else
				{
					temp = node->getData()[node->getSize() - 1];

					for (int j = node->getSize() - 1; j > i; j--)
						node->getData()[j] = node->getData()[j - 1];
					node->getData()[i] = element;

					while (node != NULL && node->isFull())
					{
						node = node->getNext();
						if (!node->isFull())
						{
							if (node->getSize() >= 1)
							{
								for (int i = node->getSize(); i > 0; i--)
									node->getData()[i] = node->getData()[i - 1];
							}
							node->getData()[0] = temp;
							node->setSize(node->getSize() + 1);
						}
						else
						{
							prevTemp = temp;
							temp = node->getData()[node->getSize() - 1];

							for (int j = node->getSize() - 1; j > 0; j--)
								node->getData()[j] = node->getData()[j - 1];

							node->getData()[0] = prevTemp;
						}
					}

				}
			}


			size++;
		}
	}

	void deleteElement(T element)
	{
		if (search(element) != NULL)
		{
			Node<T> *node = search(element);
			int i = 0;

			// sets i to the position in the array where the element is
			while (node->getData()[i] != element)
				i++;

			// moves back every element after i
			while (i < node->getSize() - 1)
			{
				node->getData()[i] = node->getData()[i + 1];
				i++;
			}

			if (node->getNext() != NULL)
				node->getData()[node->getSize() - 1] = node->getNext()->getData()[0];

			node = node->getNext();

			while (node != NULL)
			{
				for (i = 1; i < node->getSize(); i++)
					node->getData()[i - 1] = node->getData()[i];

				if (node->getNext() != NULL)
						node->getData()[node->getSize() - 1] = node->getNext()->getData()[0];

				node = node->getNext();
			}

			ptrToTail->setSize(ptrToTail->getSize() - 1);
			size--;
			if (ptrToTail->getSize() == 0 && ptrToTail != ptrToFirst)
			{
				node = ptrToFirst;
				while (node->getNext() != ptrToTail)
					node = node->getNext();
				delete ptrToTail;
				ptrToTail = node;
				ptrToTail->setNext(NULL);
			}
		}
		else
			cerr << "element not found" << endl;
	}

	int getSize() { return size; }

	Node<T>* search(T element)
	{
		Node<T>* node = ptrToFirst;
		while (node != NULL)
		{
			if (node->getSize() > 0)
			{
				for (int i = 0; i < node->getSize(); i++)
				{
					if (node->getData()[i] == element)
						return node;
				}
			}
			node = node->getNext();
		}
		return NULL;
	}

	void print() const
	{
		Node<T>* node = ptrToFirst;
		int arr = 1;
		while (node != NULL)
		{
			cout << "Array(" << arr << "):";
			for (int i = 0; i < node->getSize(); i++)
				cout << setw(3) << node->getData()[i] << " ";
			cout << endl;
			node = node->getNext();
			arr++;
		}
		cout << endl;
	}

	bool isFull() const { return (size == cap); }

	void makeEmpty()
	{
		Node<T>* node = ptrToFirst;
		while (node != NULL)
		{
			node = node->getNext();
			delete ptrToFirst;
			ptrToFirst = node;
		}
		ptrToTail = ptrToFirst;
		size = 0;
		cap = 0;

	}
	
	//destructor
	~LinkedList() {}
private:
	Node<T> *ptrToFirst;
	Node<T> *ptrToTail;
	int cap;
	int size;

};

#endif