#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class Node
{
	Node* ptr;
	string name;
	double balance;
public:
	Node() : ptr(NULL), name("None"), balance(0.0) {}
	Node(Node* p, string i, double b) : ptr(p), name(i), balance(b) {}
	void setNext(Node* p) { ptr = p; }
	void setName(string i) { name = i; }
	void setBalance(double b) { balance = b; }
	Node* getNext() const { return ptr; }
	string getName() const { return name; }
	double getBalance() const { return balance; }
	~Node() { ptr = NULL; }
};

class List
{
	Node* first;
	Node* last;
	int count;
public:
	//List reads from a text file all accounts and balances
	List()
	{
		first = NULL;
		last = NULL;
		count = 0;

		string account;
		string name;
		double bal;
		int pos;
		ifstream bank ("accounts.txt");
		if (bank.is_open())
		{
			while (getline(bank, account))
			{
				pos = account.find(" ");
				name = account.substr(0, pos);
				bal = stod(account.substr(pos + 1));
				add(name);
				search(name)->setBalance(bal);
			}
			bank.close();
		}
		else
		{
			cerr << "You don't have a bank set up." << endl;
		}
	}
	//Add adds an account to a linked list along with a zero balance
	void add(string name)
	{
		Node* node = new Node(NULL, name, 0.0);
		if (count == 0)
		{
			first = node;
			last = node;
		}
		else
		{
			if (count == 1)
			{
				first->setNext(node);
				last = node;
			}
			else
			{
				last->setNext(node);
				last = node;
			}
		}
		count++;
	}
	//AddMoney deposits a sum to any given account
	void addMoney(string name, double deposit) const
	{
		Node* node = search(name);
		node->setBalance(node->getBalance() + deposit);
	}
	//ViewBalance checks the balance of any given account
	void viewBalance(string name) const
	{
		Node* node = search(name);
		cout << node->getName() << ": " << node->getBalance() << endl;
	}
	//Interest adds a certain interest over time to all accounts
	void interest()
	{
		time_t timer;
		struct tm inter = { 0 };
		double seconds;
		inter.tm_hour = 0;
		inter.tm_min = 0;
		inter.tm_sec = 1;
		inter.tm_year = 70;
		inter.tm_mon = 0;
		inter.tm_mday = 1;
		time(&timer);
		seconds = difftime(timer, mktime(&inter));
		cout << mktime(&inter) << endl;
	}
	//Search searches for any given account
	Node* search(string name) const
	{
		Node* node = first;
		while (node->getName() != name && node != NULL)
			node = node->getNext();
		return node;
	}
	//Print prints the names of all accounts
	//Should not be accessable by a customer
	void print() const
	{
		cout << endl;
		Node* node = first;
		while (node != NULL)
		{
			cout << node->getName() << endl;
			node = node->getNext();
		}
		cout << endl;
	}
	//LogOut needs to be accessed everytime a program ends
	//otherwise progress will not be saved
	//LogOut clears and rewrites the text file
	void deleteAccount(string name)
	{
		Node* node = search(name);
		if (node == NULL)
			cerr << "The account does not exist." << endl;
		else
		{
			if (node == first)
				first = first->getNext();
			else
			{
				Node* n = first;
				while (n->getNext() != node)
					n = n->getNext();
				n->setNext(node->getNext());
			}
			delete node;
			node = NULL;
			count--;
		}
	}
	void logOut()
	{
		Node* node = first;
		ofstream bank;
		bank.open("accounts.txt", ostream::out | ostream::trunc);
		while (node != NULL)
		{
			bank << node->getName() << " " << node->getBalance() << endl;
			node = node->getNext();
		}
		bank.close();
	}
	~List()
	{
		Node* node = first;
		while (node != NULL)
		{
			first = first->getNext();
			delete node;
			node = first;
		}
	}
};