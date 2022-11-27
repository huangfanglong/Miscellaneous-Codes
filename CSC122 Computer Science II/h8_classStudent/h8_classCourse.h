#ifndef CLASS_COURSE_H
#define CLASS_COURSE_H
/*
=================================================================================
Course: Harper CSC121-122

Program Name:	Course Class
Program Description: 	
	This file declare and define class Course. 

	For Assignment 8, this .h is included. Don't change anything in this file.
	Run and play with s10c_class_course.cpp to understand this class.

Created: 3/31/2021 by Jin Guo
=================================================================================
*/
#include <string>

using namespace std;

class Course
{
public:
	Course() {} // default constructor.
	Course(string theName, string crn = "") : name(theName), CRN(crn) {}
	Course(const Course& c) : name(c.name), CRN(c.CRN) {} // copy constructor.

	string getName() const { return name; }
	string getCRN() const { return CRN.empty() ? "tbd" : CRN; }
	string toString() const;

	void setName(string theName) { name = theName; }
	void setCRN(string crn) { CRN = crn; }

private:
	string name;  // course name, e.g., "Computer Science I with C++".
	string CRN;	  // course reference number, e.g., "CSS121-S01".
};

string Course::toString() const
{
	if (CRN.empty())
		return "tbd: " + name;
	else
		return CRN + ": " + name;
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

