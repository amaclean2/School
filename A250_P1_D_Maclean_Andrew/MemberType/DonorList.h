/*
	Maclean, Andrew
	CS A250
	March 26, 2015

	Project 1D: DonorList
*/

#ifndef DONORLIST_H
#define DONORLIST_H

#include "DonorType.h"

#include<iostream>
#include <string>		
#include <iomanip>

using namespace std;

class Node
{
public:
	Node(){}
    Node(const DonorType& theDonor, Node *theLink) 
		: donor(theDonor), link(theLink){}
    Node* getLink( ) const { return link; }
	DonorType getDonor( ) const { return donor; }
    void setDonor(const DonorType& theDonor) 
		{ donor = theDonor; }
    void setLink(Node *theLink) { link = theLink; }
private:
    DonorType donor;		
    Node *link;		//pointer that points to next node
};


class DonorList
{
public:
	// default constructor
	DonorList();
	
	// addDonor
	void addDonor(const string& firstN, const string& lastN, int mNo, double donat);
	
	// searchDonorByMemberNo
	bool searchDonorByMemberNo(int mNo) const;

	// isEmpty
	bool isEmpty() const;
	
	// printAllDonors
	void printAllDonors() const;

	// destroyList
	void destroyList();
	
	// destructor
	~DonorList();

	void deleteDonor(int mNo);
	void printDonorByName(const string& lName) const;
	void printDonor(int mNo) const;
	void printDonation(int mNo) const;
	void printTotalDonations() const;
	void printHighestDonation() const;


private:
	Node* search(int mNo) const;

	Node *first;	
	Node *last;		
	int count;	

};

#endif

