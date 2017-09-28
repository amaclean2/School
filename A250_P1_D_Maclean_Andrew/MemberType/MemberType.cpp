#include "MemberType.h"

MemberType::MemberType()
{
	memberNumber = 0;
}

MemberType::MemberType(const string& first, const string& last, int memberNo)
{
	firstName = first;
	lastName = last;
	memberNumber = memberNo;
}

void MemberType::setMemberInfo(const string& first, const string& last, int memberNo)
{
	firstName = first;
	lastName = last;
	memberNumber = memberNo;
}

string MemberType::getFirstName() const
{
	return firstName;
}

string MemberType::getLastName() const
{
	return lastName;
}

int MemberType::getMembershipNo() const
{
	return memberNumber;
}

void MemberType::printName() const
{
	cout << lastName << ", " << firstName;
}

void MemberType::printMemberInfo() const
{
	cout << memberNumber << " - " << firstName << " " << lastName;
}

MemberType::~MemberType()
{

}