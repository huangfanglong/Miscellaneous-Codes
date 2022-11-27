#ifndef CLASS_STUDENT_H
#define CLASS_STUDENT_H
/*
=========================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Class inheritance with class Student and its derived classes 
Program Description:
	This file defines class Student  and its two derived classes GraduateStudent 
	and ForeignStduent. Classes Course and CourseList are defined in
	file h11_Course.h. Class FullName is defined in h11_fullName.h. Through this exercise,
	you are required to understand the concept about class hesitance, such as how to use 
	members of the parent class within the derived class declaration/definition.

Instructions:
	1. First try to understand the given program well without any changes. 
	2. Run h11_JG.out which is how your finished program should perform. Imitate 
		its prompts and output as closely as you can.
	3. You need to modify this file as follows:
		1) Add class ForeignStudent by imitating class GraduateStudent. 
		2) A foreign student has two new data members: 
			a) englishScore (unsigned), initialized to be 0.
			b) nationality (string).
	4. Add your code to wherever marked as "Your code below ...". Please do
		not remove any existing statements.
	5. When you are done, please submit ONLY the following two files:
		h11_classStudent_yrlogin.h
		h11_classStudentTest_yrlogin.cpp 

Notes: This file cannot be compiled by itself. It should be included in your 
	h11_classStudentTest_yrlogin.cpp.

Created: 	6/10/2012 by Jin Guo
Updated:	10/29/2017 by Jin Guo. Customized for Assignment 12, Harper CSC122.
Updated:	3/27/2020 by Jin Guo. Minor changes for some functions.
			Adapted for this semester.
=========================================================================================
*/
#include <iostream>
#include <iomanip>
#include <string>
#include "h11_Course.h"
#include "h11_fullName.h"

using namespace std;

class Student
{
public:
	Student() {} // default constructor
	Student(string fName, string lName, string mName = "")
		: name(fName, lName, mName)	{}
	Student(const FullName& theName) : name(theName) {}
	Student(const Student& s); // copy constructor

	string getName() const { return name.toString(); }
	void setName(string fName, string lName, string mName = "")
		{ name.setFullName(fName, lName, mName); } 

	double getGPA() const { return GPA; }
	void setGPA(double gpa) { GPA = (gpa < 0.0) ? GPA : gpa; }

	// Return course index by CRN, -1 means the course doesn't exit.
	int findCourseByCRN(string crn) const 
		{ return courseList.findCourseByCRN(crn); }

	// Return course index by course name, -1 means the course doesn't exit.
	int findCourseByName(const string& nm) const 
		{ return courseList.findCourseByName(nm); }

	// Add a course by name and its reference number.
	void addCourse(const string& classNm, const string& crn = "") 
		{ courseList.addCourse(classNm, crn); }

	// Delete a course by its reference number.
	void deleteCourseByCRN(string crn)
		{ courseList.deleteCourseByCRN(crn); }

	// Print the course list.
	void printCourseList(const string& listType) const 
		{ courseList.printList(listType); }
	
	// Print all info of Student.
	void printInfo() const; 

private:
	FullName name;
	double GPA {0.0};
	CourseList courseList; // courses registered.
};

//---------------------------------------------------------------
Student::Student(const Student& s)
{
	name = s.name;
	courseList = s.courseList;
	GPA = s.GPA;
}

void Student::printInfo() const
{
	cout << "|------------------------------------------------------\n";
	cout << "| Student: " << name.toString() << endl;
	printCourseList("Courses Taken");
	cout << "| GPA: " << fixed << setprecision(2) << GPA << "\n";
	cout << "|------------------------------------------------------\n";
}

//===============================================================
class GraduateStudent : public Student
{
public:
	GraduateStudent(string firstNm, string lastNm, string mName = "")
		: Student(firstNm, lastNm, mName) {}

	string getThesisSubject() const { return thesisSubject; }
	void setThesisSubject(const string& title) { thesisSubject = title; }

	void addCourseListTA(const string& className, string crn = "")
	{
		courseListTA.addCourse(className, crn);
	};
	void deleteCourseListTA_byCRN(const string& crn)
	{
		courseListTA.deleteCourseByCRN(crn);
	}

	void printcourseListTA() const
	{
		courseListTA.printList("Courses as TA");
	};
	void printInfo() const;

private:
	CourseList courseListTA;
	string thesisSubject;
};


//---------------------------------------------------------------

void GraduateStudent::printInfo() const
{
	Student::printInfo();
	cout << "| This is a graduate student.\n";
	cout << "| Thesis Subject: " << getThesisSubject() << endl;
	cout << "| He is TA for the following classes:\n";
	printcourseListTA();
	cout << "|------------------------------------------------------\n";
}

/*
===================================================================
Declare and define class ForeignStudent.
<<<<<< Your code below... >>>>>
===================================================================
*/
class ForeignStudent : public Student
{
public:
	ForeignStudent(string firstN, string lastN, string midN = "")
		: Student(firstN, lastN, midN) {}

	int getEnglishscore() const { return englishScore; }
	void setEnglishscore(const int& score) { englishScore = score; }

	string getNationality() const { return nationality; }
	void setNationality(const string& nation) { nationality = nation; }

	void printInfo() const;

private:
	string nationality;
	unsigned int englishScore = 0;
};

void ForeignStudent::printInfo() const
{
	Student::printInfo();
	cout << "| This is a foreign student. \n";
	cout << "| English Score: " << getEnglishscore() << endl;
	cout << "| Nationality: " << getNationality() << endl;
	cout << "|------------------------------------------------------\n";
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

