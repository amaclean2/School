#include "DonorType.h"

DonorType::DonorType()
{
	donation = 0.0;
}

DonorType::DonorType(const string& first, const string& last, int mNum, double don)
{
	setMemberInfo(first, last, mNum);
	donation = don;
}

void DonorType::setDonorInfo(const string& first, const string& last, int mNum, double don)
{
	setMemberInfo(first, last, mNum);
	donation = don;
}

void DonorType::setAmountDonated(double don)
{
	donation = don;
}

double DonorType::getAmountDonated() const
{
	return donation;
}

void DonorType::printDonor() const
{
	printMemberInfo();
}

void DonorType::printDonation() const
{
	cout << getLastName() << ", " << getFirstName() << endl;
	cout << setprecision(2) << fixed << "    Donor Amount: $" << donation << endl;
}

DonorType::~DonorType()
{

}