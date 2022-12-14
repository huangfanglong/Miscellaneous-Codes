#ifndef CLASS_NAME_H
#define CLASS_NAME_H
/*
=================================================================================
Course: Harper CSC121-122

Program Name:	Name Class
Program Description: 	
	This file declare and define class Name. 

	For Assignment 8, this .h is included. Don't change anything in this file.
	Run and play with s10b_class_name.cpp to understand this class.
	
Created: 3/31/2021 by Jin Guo
=================================================================================
*/
#include <string>

using namespace std;

class FullName
{
public:
	FullName() {} // default constructor.
	FullName(string fName, string lName, string mName = "")
		{ setFullName(fName, lName, mName); }
	FullName(const FullName& n) // copy constructor.
		: firstName(n.firstName), lastName(n.lastName), middleName(n.middleName) {}
		
	// Accessors.
	string getFirstName() const { return firstName; }
	string getLastName() const { return lastName; }
	string getMiddleName() const { return middleName; }
	string toString() const;

	// Mutators.
	void setFirstName(string fName) { firstName = fName.substr(0, nameLength); }
	void setLastName(string lName) { lastName = lName.substr(0, nameLength); }
	void setMiddleName(string mName) { middleName = mName.substr(0, nameLength); }
	void setFullName(string lName, string fName, string mName = "");

private:
	string firstName;
	string lastName;
	string middleName;

	static const int nameLength = 10;
};

//==============================================================
string FullName::toString() const
{
	if (firstName.empty() && lastName.empty() && middleName.empty())
		return "";
	
	string middleInitial;
	if (!middleName.empty())
		middleInitial = middleName.substr(0, 1) + ". ";

	return lastName + ", " + middleInitial + firstName;
}

void FullName::setFullName(string fName, string lName, string mName)
{
	firstName = fName.substr(0, nameLength);
	lastName = lName.substr(0, nameLength);
	middleName = mName.substr(0, nameLength);
}

/*
************************************************
* (C) Copyright - by Jin Guo
*
* This program is free for my class students.
* For any other purpose of using this program,
* please ask for permission by sending email to:
* taiji.guo@gmail.com
************************************************
*/
#endif

