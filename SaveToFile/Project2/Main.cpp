#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node
{
	string value;
	double balance;
	Node* ptr;
public:
	Node() : value(0), ptr(NULL), balance(0.0) {}
	Node(string i, Node* n, double d) : value(i), ptr(n), balance(d) {}
	void setValue(string i) { value = i; }
	void setPtr(Node* n) { ptr = n; }
	void setBalance(int i) { balance = i; }
	string getValue() const { return value; }
	Node* getPtr() const { return ptr; }
	double getBalance() { return balance; }
	~Node();
};

class List
{
	Node* first;
	Node* last;
	int count;
public:
	List()
	{
		string line;
		string name;
		double bal;
		int pos;
		ifstream myfile("list.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				pos = line.find(" ");
				name = line.substr(0, pos);
				bal = stod(line.substr(pos + 1));
				add(name);
				deposit(name, bal);
			}
			myfile.close();
		}
		else
			cerr << "file does not exist." << endl;

		first = NULL;
		last = NULL;
		count = 0;
	}
	void add(string i)
	{
		Node* node = new Node(i, NULL, 0.0);
		if (count == 0)
		{
			first = node;
			last = node;
		}
		else
		{
			if (count == 1)
			{
				first->setPtr(node);
				last = node;
			}
			else
			{
				last->setPtr(node);
				last = node;
			}
		}
		count++;
	}
	void deleteAccount(string i)
	{
		Node* node = search(i);
		delete node;
	}
	void write() const 
	{
		Node* node = first;
		ofstream myfile;
		myfile.open("list.txt", ostream::out | ostream::trunc);

		while (node != NULL)
		{
			myfile << node->getValue() << " " << node->getBalance() << endl;
			node = node->getPtr();
		}
		myfile.close();
	}
	void deposit(string s, double d)
	{
		Node* node = search(s);
		node->setBalance(node->getBalance() + d);
	}
	Node* search(string i) const
	{
		Node* node = first;
		while (node->getValue() != i && node != NULL)
			node = node->getPtr();
		return node;
	}
	~List()
	{
		Node* node = first;
		while (node != NULL)
		{
			first = first->getPtr();
			delete node;
			node = first;
		}
	}
};

int main()
{
	system("title database program");
	system("color 0F");

	List* list = new List();
	list->add("andrew");
	list->add("brian");
	list->add("lindsey");
	list->add("cubby");
	list->deposit("andrew", 20.00);
	list->write();

	list->deposit("brian", 23.00);
	list->write();

	system("pause");
	system("cls");

	system("pause");
	return 0;
}