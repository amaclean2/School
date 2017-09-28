/*
	Maclean, Andrew
	CS A250
	February, 10th, 2015
*/

#ifndef MEMBERTYPE_H
#define MEMBERTYPE_H

#include <iostream>
#include <string>

using namespace std;

class MemberType
{
public:
	MemberType();

	MemberType(const string& first, const string& last, int memberNo);

	void setMemberInfo(const string& first, const string& last, int memberNo);

	string getFirstName() const;

	string getLastName() const;

	int getMembershipNo() const;

	void printName() const;

	void printMemberInfo() const;

	~MemberType();

private:
	string firstName;
	string lastName;
	int memberNumber;

};

#endif