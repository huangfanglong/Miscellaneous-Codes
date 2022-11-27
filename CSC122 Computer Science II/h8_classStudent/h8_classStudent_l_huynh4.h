h#ifndef CLASS_STUDENT_H
#define CLASS_STUDENT_H
/*
=========================================================================================
Course: Harper CSC122-002 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Student Class
Program Description:
	This .h file declares and defines class Student, which contains some basic info 
	of a student such as name, course list, GPA, etc. We will extend this class 
	naturally by using more constructs of C++ class in later studying. This assignment
	gives you exercises on adding data members and member functions to an existing class.

Instructions:
	1. There are four files in this program under dir h8_classStudent. You only need 
		to change two of them.
		1) h8_className.h // included in h8_classStudent.h and h8_classStudentsTest.cpp.
			Don't change anything in this file.
		2) h8_classCourse.h // included in h8_classStudent.h. Don't change anything
			in this file.
		3) h8_classStudent.h // rename this file with your login and change it as needed.
		4) h8_classStudentsTest.cpp // rename this file with your login and change it 
			as needed.
	2. Understand, compile and run the given program before you do any change. Just type:
		"g++ *.cpp" under the dir h8_classStudent to compile this program.
		Also run h8_JG.out on Unix, which is how your finished program should perform. 
		Imitate exactly its output.
	3. Your jobs in this file are:
		1) Add a private data member GPA in class Student. Keep GPA > 0.0.
		2) Modify the following existing functions with GPA processing.
			a. The copy constructor.
			b. printInfo().
		3) Add the following new member functions:
			a. A new constructor with a new parameter for GPA. 
			b. getGPA() and setGPA(). 
			c. findCourseByCRN(..). 
			d. deleteCourseByCRN().
	4. Add your code to wherever marked as "Your code below ...". In the comments, more 
		info is given for new functions. Please do not remove any existing statements.
	5. When you are done with this file, add your testing code in main() in your
		h8_classStudentsTest_yrlgoin.cpp. Read instructions in the .cpp file.
	6. Submit only the following two files. Name them properly as usual.
		h8_classStudent_yrlogin.h and h8_classStudentsTest_yrlgoin.cpp
		
Notes: 
	1. If a member function has only one statement, define it within the class
		declaration.
	2. You may initialize a data member of built-in type (e.g., int) within the 
		class declaration. Refer to fig03_08-09 of textbook code.

Created: 	6/10/2012 by Jin Guo
Modified:	10/25/2017 by Jin Guo. Customized for Harper CSC122.
Modified:	3/31/2021 by Jin Guo. Significant changes for this semester.
=========================================================================================
*/
#include <string>
#include <vector>
#include <iostream>
#include <iomanip> // for setprecision(), fixed.
#include "h8_className.h"	
#include "h8_classCourse.h"	

using namespace std;

class Student
{
public:
	Student() {} // default constructor
	Student(string fName, string lName, string mName)
		: name(fName, lName, mName) {}	
	Student(const FullName& theName) : name(theName) {}
	Student(const Student& s); // copy constructor

	string getName() const { return name.toString(); }
	void setName(string fName, string lName, string mName = "");

	void addCourse(const string& className, string crn = "");
	void printCourseList() const;	// print the course list.
	void printInfo() const;			// print the student info.

	/**
	Return the course index in data member courseList by course name, 
	-1 means the course doesn't exit.
	*/
	int findCourseByName(const string& name) const;

	/*
	====================================================================
	Notes: If a function can be defined with one statement, define it 
		along with its declaration. Refer to member function getName().

	>>> Add the following member functions ...

	// Constructor with a GPA parameter.
	Student(string fName, string lName, string mName, double gpa);	

	getGPA(..)	// return GPA.
	setGPA(..)	// modify GPA.

	// Return the course index in data member courseList by CRN (course reference 
	// number), -1 means the course doesn't exit. Refer to findCourseByName().
	int findCourseByCRN(const string& crn) const;

	// Delete a course by its reference number. 
	void deleteCourseByCRN(const string& crn); 

	<<<<<< Your code below ... >>>>>
	==========================================================
	*/
	Student(string fName, string lName, string mName, double gpa)
		: name(fName, lName, mName) {
		setGPA(gpa);
	}

	double getGPA() const { return GPA; } // accessor

	void setGPA(double gpa) // mutator
	{ 
		GPA = (gpa >= 0.0) ? gpa : GPA;
	} 
	
	int findCourseByCRN(const string& crn);
	void deleteCourseByCRN(const string& crn);
	

private:
	FullName name;
	vector<Course> courseList;

	/*
	================================================================
	Add a double data member GPA below.
	<<<<<< Your code below ... >>>>>
	================================================================
	*/
	double GPA{ 0.0 };

};

//====================================================================
void Student::setName(string fName, string lName, string mName)
{
	name.setFullName(fName, lName,mName);
}

void Student::addCourse(const string& className, string crn)
{
	Course new_class(className, crn);
	courseList.push_back(new_class);
}

void Student::printCourseList() const
{
	size_t size = courseList.size();
	if (size == 0)
	{
		cout << "| Courses taken: None\n";
		return;
	}

	cout << "| Courses taken: \n";
	for (size_t i = 0; i < size; ++i)
		cout << "|   " << courseList[i].toString() << "\n";
}

int Student::findCourseByName(const string& nm) const
{
	int pos = -1;
	for (size_t i = 0; i < courseList.size(); i++)
	{
		if (nm == courseList[i].getName())
		{
			pos = i;
			break;
		}
	}

	return pos;
}

/*
=====================================================================================
1. Modify the copy constructor so GPA is also copied.
2. Modify printInfo() so GPA is also printed out.

<<<<<< Your code below ... >>>>>
=====================================================================================
*/
Student::Student(const Student& s) // copy constructor.
{
	name = s.name;
	courseList = s.courseList;
	GPA = s.GPA;
}

void Student::printInfo() const
{
	cout << "-------------------------------------------\n";
	cout << "| Student: " << name.toString() << endl;
	printCourseList();
	cout << "| GPA: " <<fixed<<setprecision(2)<< GPA << endl;
	cout << "-------------------------------------------\n";
}

/*
=====================================================================================
Define those class member functions you added in the declaration of class Student.

Hints for defining deleteCourseByCRN(..): 
1. Call findCourseByCRN() to get the index for the course to be deleted. If the index 
	is -1, print info to indicate that the course doesn't exist; otherwise continue.
2. Shift the courses from the position of the found course so memory is not wasted.
3. Delete the last element in courseList.

<<<<<< Your code below ... >>>>>
=====================================================================================
*/
int Student::findCourseByCRN(const string& crn)
{
	int pos = -1;
	for (size_t i = 0; i < courseList.size(); i++)
	{
		if (crn == courseList[i].getCRN())
		{
			pos = i;
			break;
		}
	}

	return pos;
}

void Student::deleteCourseByCRN(const string& crn)
{
	int pos = findCourseByCRN(crn);
	if (pos == -1)
	{
		cout << "The course "<< crn <<" does not exist!";
	}
	else
	{
		courseList.erase(courseList.begin() + pos);
		courseList.pop_back();
		cout << "Course " << crn << " was deleted!";
	}
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

