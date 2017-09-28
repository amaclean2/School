#include "AnyList.h"

	//constructor
AnyList::AnyList()
{
	ptrToFirst = NULL;
	count = 0;
}

	//print
void AnyList::print() const
{
	if (ptrToFirst == NULL)
		cerr << "empty";
	else
	{
		Node *current;	//create a pointer to traverse the list 
		current = ptrToFirst;	//set the current pointer to point to the first node

		while (current != NULL)	//while the current pointer is not pointing to NULL
		{						//  that is, the current pointer has not reached the 
			//  end of the list
			cout << current->getData() << " ";	//output the data 
			current = current->getPtrToNext();		//move the current pointer forward
		}
	}
}

	//destroyList
void AnyList::destroyList()
{ 
    Node  *temp; //pointer to delete the node
	
	while (ptrToFirst != NULL)
    {
		temp = ptrToFirst;
		ptrToFirst = ptrToFirst->getPtrToNext();
        delete temp;
		temp = NULL;
    }

	count = 0;
}

	//destructor
AnyList::~AnyList()
{
	destroyList();
}

/*************************************************

		Write your code below this line.

*************************************************/

//Definition function getNumOfItems
int AnyList::getNumOfItems() const
{
	return count;
}




//Definition of function insertBack()
void AnyList::insertBack(const int numInserted)
{
	//creates a new node and fills it with the number given and a pointer to NULL
	Node* node = new Node(numInserted, NULL);
	// if there are no nodes in the list, ptrToFirst points to the new node
	if (count == 0)
	{
		ptrToFirst = node;
	}
	// otherwise a while loop searches for the last node in the list and makes that point to the new node
	else
	{
		Node* current = ptrToFirst;
		while (current->getPtrToNext() != NULL)
		{
			current = current->getPtrToNext();
		}
		current->setPtrToNext(node);
	}
	// count is increased
	count++;
}



//Definition function deleteFirstNode
void AnyList::deleteFirstNode()
{
	if (count == 0)
	{
		cerr << "Cannot delete from an empty list";
	}
	else
	{
		Node* temp = ptrToFirst->getPtrToNext();
		delete ptrToFirst;
		ptrToFirst = temp;
		count--;
	}
}
