#include "DonorList.h"

// default constructor
DonorList::DonorList()
{
	first, last = NULL;
	count = 0;
}

// addDonor
void DonorList::addDonor(const string& firstN, const string& lastN, int mNo, double donat)
{
	DonorType entry = DonorType(firstN, lastN, mNo, donat);
	Node *node = new Node(entry, NULL);
	if (count == 0)
	{
		first = node;
		last = node;
	}
	else
	{
		last->setLink(node);
		last = node;
	}
	count++;
}

// searchDonorByMemberNo
bool DonorList::searchDonorByMemberNo(int mNo) const
{
	Node *node = first;
	while (node != NULL && !true)
	{
		return (node->getDonor().getMembershipNo() == mNo);
		node = node->getLink();
	}
}

// isEmpty
bool DonorList::isEmpty() const
{
	return count == 0;
}

// printAllDonors
void DonorList::printAllDonors() const
{
	Node *node = first;
	while (node != NULL)
	{
		node->getDonor().printMemberInfo();
		node = node->getLink();
		cout << endl;
	}
}

// destroyList
void DonorList::destroyList()
{
	Node *node;
	while (first != NULL)
	{
		node = first;
		first = first->getLink();
		delete node;
		node = NULL;
		count--;
	}
}

// destructor
DonorList::~DonorList()
{
	destroyList();
}

void DonorList::deleteDonor(int mNo)
{
	//count is 0
	if (count == 0)
		cerr << "Cannot delete from an empty list." << endl;

	//count is 1
	else if (count == 1)
	{
		delete first;
		first = NULL;
		last = NULL;
		count = 0;
	}

	//count is more than 1
	else
	{
		Node *c = first;
		Node *tc = first;

		// is the first node
		if (first->getDonor().getMembershipNo() == mNo)
		{
			c = first->getLink();
			delete first;
			first = c;
			count--;
		}

		// is not the first node
		else
		{
			bool result = false;
			while (c != NULL)
			{
				// is in the list
				if (c->getDonor().getMembershipNo() == mNo)
				{
					tc->setLink(c->getLink());
					delete c;
					c = NULL;
					count--;
					result = true;
				}

				tc = c;
				c = c->getLink();
			}

			// is not in the list
			if (result == false)
				cerr << "That member number isn't in the list.";

			// reposition last
			c = first;
			while (c != NULL)
				c = c->getLink();
			last = c;
		}

	}
}

void DonorList::printDonorByName(const string& lName) const
{
	Node *node = first;
	bool result = false;
	while (node != NULL)
	{
		if (node->getDonor().getLastName() == lName)
		{
			node->getDonor().printMemberInfo();
			result = true;
			node = NULL;
		}
		node = node->getLink();
	}

	if (result == false)
		cerr << "Member not in the list." << endl;
}

void DonorList::printDonor(int mNo) const
{
	if (search(mNo) == NULL)
		cerr << "That member isn't in the list.";
	else {
		search(mNo)->getDonor().printMemberInfo();
	}
}

void DonorList::printDonation(int mNo) const
{
	if (search(mNo) == NULL)
		cerr << "That member isn't in the list.";
	else
		search(mNo)->getDonor().printDonation();
}

void DonorList::printTotalDonations() const
{
	Node *node = first;
	double tDonations = 0.0;
	while (node != NULL)
	{
		tDonations += node->getDonor().getAmountDonated();
		node = node->getLink();
	}
	cout << setprecision(2) << fixed << "Total Donations: $" << tDonations << endl;
}

void DonorList::printHighestDonation() const
{
	Node *node = first;
	double highestDonation = 0.0;
	Node *highest = NULL;
	while (node != NULL)
	{
		if (node->getDonor().getAmountDonated() > highestDonation)
		{
			highestDonation = node->getDonor().getAmountDonated();
			highest = node;
		}
		node = node->getLink();
	}
	cout << setprecision(2) << fixed << "Highest Donation: $" << highestDonation << endl;
	cout << "    Donated by: " << highest->getDonor().getLastName() << ", " << highest->getDonor().getFirstName();
}

Node* DonorList::search(int mNo) const
{
	Node *node = first;

	while (node != NULL && node->getDonor().getMembershipNo() != mNo)
		node = node->getLink();

	return node;
}
