/*
=========================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Class Inheritance
Program Description:
	This file tests class Student and its two derived classes GraduateStudent 
	and ForeignStduent. Classes Course and CourseList are defined in
	file h11_Course.h. Class FullName is defined in h11_fullName.h. Through this exercise,
	you are required to understand the concept about class inheritance, such as how to use 
	members of the parent class within the derived class declaration/definition.

Instructions:
	1. First try to understand the three .h files and this .cpp file. 
	2. Run h11_JG.out which is how your finished program should perform. Imitate 
		its prompts and output as precisely as you can.
	3. You need to modify this .cpp file by adding code to test class ForeignStduent 
		you declared and defined in your h11_Student_yrlogin.h. Please do not remove any 
		existing statements in this file.
	4. When you are done, please submit ONLY the following two files:
		h11_classStudent_yrlogin.h
		h11_classStudentTest_yrlogin.cpp 
Notes: 
	1. You need all the four files in the same directory in order to compile this program.
	2. On line 37 in your h11_classStudentTest_yrlogin.cpp, please include your 
		h11_classStudent_yrlogin.h in place of h11_classStudent.h

Created: 6/10/2012 by Jin Guo
Updated: 10/29/2017 by Jin Guo. Customized for Assignment 12, Harper CSC122.
Updated: 3/27/2020 by Jin Guo. Minor changes for some functions.
			Adapted for this semester.
Updated: 5/4/2021. Simplified some code.
=========================================================================================
*/
#include <iostream>
#include "h11_classStudent_l_huynh4.h" 

using namespace std;

int main()
{
	// Print header.
	cout << "===============================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #11, Spring 2021\n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program defines and tests Student class and its two\n";
	cout << "derived classes GraduateStudent and ForeignStudent.\n";
	cout << "===============================================================\n\n";;

	cout << ">>> Create a blank student s1 with default constructor ...\n";
	Student s1;

	cout << ">>> Set name with \"Mary Roca\" ...\n";
	s1.setName("Mary", "Roca");
	cout << ">>> Add course \"CSC 213 Data Structure\" ...\n";
	s1.addCourse("CSC 213 Data Structure");
	cout << "\nPrint s1 by s1.printInfo():\n";
	s1.printInfo();

	cout << "\n>>> Create student s2 for \"John Anthony Gary\" ...\n";
	Student s2("John", "Gary", "Anthony");

	cout << ">>> Set GPA = 3.3 and add some courses to s2 ...\n";
	s2.setGPA(3.3);
	s2.addCourse("CPSC 345 Computer Architecture", "23136");
	s2.addCourse("MATH 321 Calculus", "12345");
	s2.addCourse("CPCS 214 Introduction to Algorithm", "34521");
	s2.addCourse("CPCS 358 Computer Graphics", "67895");	
	cout << "\nPrint s2 by s2.printInfo():\n";
	s2.printInfo();

	cout << "\n>>> Try to delete some courses from s2 ...\n\n";
	s2.deleteCourseByCRN("12345");
	s2.deleteCourseByCRN("23332");
	cout << "\nPrint s2 by s_pt->printInfo() to access Student::printInfo(),\n";
	Student* s_pt = &s2;
	s_pt->printInfo();

	cout << "\n";
	cout << "==========================================================\n";
	cout << "<<<<< Testing code for class GraduateStudent ... >>>>>\n";
	cout << "==========================================================\n\n";

	cout << ">>> Create graduate student gs with \"Edison Bush\" ...\n";
	GraduateStudent gs("Edison", "Bush", "");

	cout << ">>> Set GPA = 4.2 and add some courses to gs ...\n";
	gs.setGPA(4.2);
	gs.addCourse("CPCS 214 Introduction to Algorithm", "34521"); // base class member
	gs.addCourse("CPCS 345 Advanced Operating System", "34671"); // base class member

	cout << ">>> Add a thesis title to the above student ...\n";  
	gs.setThesisSubject("Design A Robot Which Can Climb"); // derived class member
	cout << ">>> Add a TA class to the above student ...\n";
	gs.addCourseListTA("CPSC 345 Computer Architecture", "23136"); // derived class member 

	cout << "\nPrint gs by gs.printInfo() to access GraduateStudent::printInfo(),\n";
	gs.printInfo();

	cout << "\n";
	cout << "==========================================================\n";
	cout << "<<<<< My testing code for class ForeignStudent ... >>>>>\n";
	cout << "==========================================================\n\n";
	/*
	==========================================================
	Add your testing code for the ForeignStudent class.
	<<<<<< Your code below... >>>>>
	==========================================================
	*/
	cout << ">>> Create foreign student fs with name \"Shelley Lin\" ...\n";
	ForeignStudent fs("Shelley", "Lin", "");
	fs.printInfo();

	cout << ">>> Set nationality and English score to fs ... \n";
	fs.setNationality("Japan");
	fs.setEnglishscore(580);

	cout << ">>> Add some courses to fs ... \n";
	fs.addCourse("CPCS 358 Computer Graphics", "67895");
	fs.addCourse("CPSC 345 Computer Architecture", "23136");

	fs.printInfo();
}

/* A Sample Output
===============================================================
Harper CSC122-S01 by Mr. Jin Guo: Assignment #11, Spring 2021
Student: Long Huynh

This program defines and tests Student class and its two
derived classes GraduateStudent and ForeignStudent.
===============================================================

>>> Create a blank student s1 with default constructor ...

Print s1 by s2.printInfo():
|------------------------------------------------------
| Student:
| Courses Taken: None
| GPA: 0.00
|------------------------------------------------------

>>> Set name with "Mary Roca" ...
>>> Add course "CSC 213 Data Structure" ...

Print s1 by s1.printInfo():
|------------------------------------------------------
| Student: Roca, Mary
| Courses Taken:
|     CRN: tbd | CSC 213 Data Structure
| GPA: 0.00
|------------------------------------------------------

>>> Create student s2 for "John Anthony Gary" ...
>>> Set GPA = 3.3 and add some courses to s2 ...

Print s2 by s2.printInfo():
|------------------------------------------------------
| Student: Gary, John A.
| Courses Taken:
|     CRN: 23136 | CPSC 345 Computer Architecture
|     CRN: 12345 | MATH 321 Calculus
|     CRN: 34521 | CPCS 214 Introduction to Algorithm
|     CRN: 67895 | CPCS 358 Computer Graphics
| GPA: 3.30
|------------------------------------------------------

>>> Try to delete some courses from s2 ...

!!!Course 12345 was deleted!!!
!!!Course 23332 is not in the course list!!!

Print s2 by s_pt->printInfo() to access Student::printInfo(),
|------------------------------------------------------
| Student: Gary, John A.
| Courses Taken:
|     CRN: 23136 | CPSC 345 Computer Architecture
|     CRN: 34521 | CPCS 214 Introduction to Algorithm
|     CRN: 67895 | CPCS 358 Computer Graphics
| GPA: 3.30
|------------------------------------------------------

==========================================================
<<<<< Testing code for class GraduateStudent ... >>>>>
==========================================================

>>> Create graduate student gs with "Edison Bush" ...

>>> Set GPA = 4.2 and add some courses to gs ...
>>> Add a thesis title to the above student ...
>>> Add a TA class to the above student ...

Print gs by gs.printInfo() to access GraduateStudent::printInfo(),
|------------------------------------------------------
| Student: Bush, Edison
| Courses Taken:
|     CRN: 34521 | CPCS 214 Introduction to Algorithm
|     CRN: 34671 | CPCS 345 Advanced Operating System
| GPA: 4.20
|------------------------------------------------------
| This is a graduate student.
| Thesis Subject: Design A Robot Which Can Climb
| He is TA for the following classes:
| Courses as TA:
|     CRN: 23136 | CPSC 345 Computer Architecture
|------------------------------------------------------

==========================================================
<<<<< My testing code for class ForeignStudent ... >>>>>
==========================================================

>>> Create a foreign student fs with name "Shelley Lin"

Print fs by fs.printInfo():
|------------------------------------------------------
| Student: Lin, Shelley
| Courses Taken: None
| GPA: 0.00
|------------------------------------------------------
| This is a foreign student.
| English Score: 0
| Nationality:
|------------------------------------------------------

>>> Set nationality and English score to fs ...
>>> Add some courses to fs ...

Print fs by fs.printInfo() to access ForeignStudent::printInfo(),
|------------------------------------------------------
| Student: Lin, Shelley
| Courses Taken:
|     CRN: 67895 | CPCS 358 Computer Graphics
|     CRN: 23136 | CPSC 345 Computer Architecture
| GPA: 0.00
|------------------------------------------------------
| This is a foreign student.
| English Score: 580
| Nationality: Japan
|------------------------------------------------------

*/

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

