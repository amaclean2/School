/*
Maclean, Andrew
CS A250
February, 10th, 2015
*/

#ifndef DONORTYPE_H
#define DONORTYPE_H

#include <iostream>
#include <iomanip>
#include <string>
#include "MemberType.h"

using namespace std;

class DonorType: public MemberType
{
public:	
	DonorType();
	DonorType(const string& first, const string& last, int mNum, double don);
	void setDonorInfo(const string& first, const string& last, int mNum, double don);
	void setAmountDonated(double don);
	double getAmountDonated() const;
	void printDonor() const;
	void printDonation() const;
	~DonorType();
	
private:
	double donation;
};

#endif



