#ifndef COURSE_H
#define COURSE_H
/*
====================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021

Program Name: Course and CourseList classes 
Program Description:
	This file declares and defines classes Course and CourseList. 

	For Assignment 11, this .h is to be included. Don't change anything in this file.
	Refer to s10c_class_course.cpp and h8_classStudent.h.

Created: 	6/10/2012 by Jin Guo.
Updated:	10/29/2017 by Jin Guo. Customized for Harper CSC122.
Updated:	3/27/2020 by Jin Guo. Minor improvements.
Updated:	5/3/2021 by Jin Guo. Some improvements.
=====================================================================================
*/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>	// for setw()

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
	string output;
	if (CRN.empty())
		output = "|     CRN: tbd | " + name + "\n";
	else
		output = "|     CRN: " + CRN + " | " + name + "\n";

	return output;
}

//============================================================
class CourseList
{
public:
	CourseList() {}

	// Return course index by CRN, -1 means the course doesn't exit.
	int findCourseByCRN(const string& crn) const;

	// Return course index by course name, -1 means the course doesn't exit.
	int findCourseByName(const string& name) const;

	// Add a course to courseList, crn can be determined later.
	void addCourse(const string& className, const string& crn = "tbd");

	// Delete course by its reference number. The memory is released.
	void deleteCourseByCRN(const string& crn); 

	// Print out the course list.
	void printList(const string& listType) const; 

private:
	vector<Course> courseList;
};

//------------------------------------------------------------
int CourseList::findCourseByCRN(const string& crn) const
{
	int pos = -1;

	for (size_t i = 0; i < courseList.size(); ++i)
	{
		if (crn == courseList[i].getCRN())
		{
			pos = i;
			break;
		}
	}

	return pos;
}

int CourseList::findCourseByName(const string& nm) const
{
	int pos = -1;

	for (size_t i = 0; i < courseList.size(); ++i)
	{
		if (nm == courseList[i].getName())
		{
			pos = i;
			break;
		}
	}

	return pos;
}

void CourseList::addCourse(const string& className, const string& crn)
{
	Course newClass(className, crn);
	courseList.push_back(newClass);
}

void CourseList::deleteCourseByCRN(const string& crn)
{
	int pos = findCourseByCRN(crn);
	if (pos == -1)
	{
		cout << "!!!Course " << crn << " is not in the course list!!!\n";
		return;
	}

	/*
	size_t size = courseList.size();
	for (size_t i = pos; i < size - 1; i++)
	courseList[i] = courseList[i + 1];

	courseList.pop_back();
	*/
	courseList.erase(courseList.begin() + pos);

	cout << "!!!Course " << crn << " was deleted!!!\n";
}

void CourseList::printList(const string& listType) const
{
	size_t size = courseList.size();
	if (size == 0)
	{
		cout << "| " << listType << ": None\n";
		return;
	}

	cout << "| " << listType << ":\n";
	for (size_t i = 0; i < size; ++i)
		cout << courseList[i].toString();
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

