#include "SymbolTable.h"

LinkedList::LinkedList()
{
	ptrToFirst = NULL;
}

void LinkedList::insert(const string& insertedData, int scope)
{
	Node *index = ptrToFirst;
	Node *node = new Node(insertedData, scope, NULL);
	if (index == NULL)
		ptrToFirst = node;
	else
	{
		while (index->getNext() != NULL && !(index->getData() == insertedData && index->getScope() == scope))
			index = index->getNext();
		if (!(index->getData() == insertedData && index->getScope() == scope))
		{
			node->setNext(ptrToFirst);
			ptrToFirst = node;
		}
	}
}

Node* LinkedList::search(const string& searchTerm)
{
	if (ptrToFirst == NULL)
		return NULL;
	else
	{
		Node *node = ptrToFirst;
		while (node != NULL && node->getData() != searchTerm)
			node = node->getNext();
		if (node->getData() == searchTerm)
			return (node);
	}
}

bool LinkedList::empty()
{
	return (ptrToFirst == NULL);
}

void LinkedList::print() const
{
	Node *node = new Node();
	// do some printing function in the style of whatever way your professor asks...
	if (ptrToFirst != NULL)
	{
		node = ptrToFirst;
		cout << "( " << node->getData() << ", " << node->getScope() << " ) ";
		while (node->getNext() != NULL)
		{
			node = node->getNext();
			cout << "( " << node->getData() << ", " << node->getScope() << " ) ";
		}
	}
	else
		cout << "There is no information in this list" << endl;
}

void LinkedList::del(int scope)
{
	Node *node = ptrToFirst;
	Node *trailingNode = new Node();
	while (node != NULL)
	{
		while (node != NULL && node->getScope() != scope)
		{
			trailingNode = node;
			node = node->getNext();
		}

		if (node != NULL)
		{
			//deletes the item from the list and pushes it onto the stack
			if (node == ptrToFirst && node->getNext() == NULL)
			{
				ptrToFirst = NULL;
				tempStack.push(node->getData());
				node = NULL;
			}
			else if (node == ptrToFirst && node->getNext() != NULL)
			{
				ptrToFirst = node->getNext();
				tempStack.push(node->getData());
				node = ptrToFirst;
			}
			else if (node != ptrToFirst && node->getNext() == NULL)
			{
				trailingNode->setNext(NULL);
				tempStack.push(node->getData());
				node = NULL;
			}
			else if (node != ptrToFirst && node->getNext() != NULL)
			{
				node = node->getNext();
				trailingNode->setNext(node);
				tempStack.push(node->getData());
			}
		}
		//one item has been deleted or there was nothing to delete in the list
	}
	//there's nothing else to delete
}



HashTable::HashTable()
{
	for (int i = 0; i < 23; i++)
		table[i] = new LinkedList();
	localScope = 0;
}

int HashTable::convertString(const string& strToConvert)
{
	int sum = 0;
	unsigned size = strToConvert.size();
	for (int i = 0; i < size; i++)
		sum += strToConvert[i];

	int key = (sum + 255) % 23;
	return key;
}

void HashTable::insert(const string& data)
{
	table[convertString(data)]->insert(data, localScope);
	table[convertString(data)]->search(data);
}

void HashTable::print() const
{
	for (int i = 0; i < 23; i++)
	{
		cout << i << ": ";
		if (!table[i]->empty())
			table[i]->print();
		cout << endl;
	}
}

string HashTable::find(const string& searchString)
{
	int a = convertString(searchString);
	if (table[a]->search(searchString) != NULL)
		return table[a]->search(searchString)->getData();
	else
		return "Not Found";
}

void HashTable::newScope()
{
	localScope++;
}

void HashTable::closeScope()
{
	if (localScope > 0)
	{
		for (int i = 0; i < 23; i++)
		{
			table[i]->del(localScope);
			while (!table[i]->getStack().empty())
			{
				obsoleteVariables.push(table[i]->getStack().top());
				table[i]->remove();
			}
		}
		localScope--;
	}

}