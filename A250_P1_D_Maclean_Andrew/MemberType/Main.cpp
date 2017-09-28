/*
	(name header)
*/

#include "DonorList.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readData(DonorList& donorList);
void createDonorList(ifstream& infile, DonorList& donorList);
void displayMenu();
void processChoice(DonorList& donorList);

int main()
{
	DonorList donorList;

	readData(donorList);
	displayMenu();
	processChoice(donorList);

	cout  <<  endl;
	system("Pause");
	return 0;
}

void readData(DonorList& donorList)
{
	ifstream infile;

	infile.open("donors_data.txt");

	if(!infile)
	{
		cerr << "Input file does not exist." << endl;
		exit(1);
	}

	createDonorList(infile, donorList);

	infile.close();
}

void createDonorList(ifstream& infile, DonorList& donorList)
{
	string  fName, lName;
	int memberNo;
	double donation;

	infile >> fName;
	
	while(infile)
	{
		infile >> lName;
		infile >> memberNo;
		infile >> donation;

		donorList.addDonor(fName, lName, memberNo, donation);

		infile >> fName;
	}
}

void displayMenu()
{
	cout << "\n*** MAIN MENU ***\n";
	cout << "\nSelect one of the following:\n\n";
	cout << "    1: Add a donor" << endl;
	cout << "    2: Delete a donor" << endl;
	cout << "    3: Find a donor by name" << endl;
	cout << "    4: Find a donor by membership number" << endl;
	cout << "    5: Print all donors" << endl;
	cout << "    6: Print a donor's donation" << endl;
	cout << "    7: Print total donations" << endl;
	cout << "    8: Print highest donation and donor's information" << endl;
	cout << "    9: To exit" << endl;
}

void processChoice(DonorList& donorList)
{
	int choice;
	cout << "\nEnter your choice: ";
	cin >> choice; 
	cout << endl;

	while (choice != 9)
	{
		string fName, lName;
		int memberNo = 0;
		double donation = 0.0;

		switch(choice)
		{
			// Add a donor
		case 1: 
			cout << "Enter donor's first name, last name, membership number,"
				<< " and amount donated:\n";
			cin >> fName >> lName >> memberNo >> donation;
			cout << endl;
			/*
				We are using search here because the addDonor function
				simply adds a donor at the end of the list without 
				checking if the donor is already in the list. 
			*/
			if (donorList.searchDonorByMemberNo(memberNo))
				cerr << "This donor member number is already in the list." << endl;
			else
			{
				donorList.addDonor(fName, lName, memberNo, donation);
				cout << "Donor has been added." << endl;
			}
			break;

			// Delete a Donor
		case 2:
			cout << "Enter a membership number of a donor you want to delete:";
			cin >> memberNo;
			cout << endl;
			donorList.deleteDonor(memberNo);
			cout << endl;
			cout << "Donor has been deleted." << endl;
			break;
			
		case 3:
			cout << "Enter a donor's last name:";
			cin >> lName;
			cout << endl;
			donorList.printDonorByName(lName);
			cout << endl;
			break;
			
		case 4:
			cout << "Enter a donor's membership number:";
			cin >> memberNo;
			cout << endl;
			donorList.printDonor(memberNo);
			cout << endl;
			break;

		case 5: 
			if (donorList.isEmpty())
				cerr << "There are no donors in the list.";
			else
				donorList.printAllDonors();
			cout << endl;
			break;

		case 6:
			cout << "Enter a donor's member number: ";
			cin >> memberNo;
			donorList.printDonation(memberNo);
			break;

		case 7:
			donorList.printTotalDonations();
			break;

		case 8:
			donorList.printHighestDonation();
			cout << endl;
			break;

		default: 
			cout << "\nSorry. That is not a selection." << endl;
			break;
		}

		displayMenu();
		cout << "\nEnter your choice: ";
		cin >> choice;
		cout << endl;
	}
}