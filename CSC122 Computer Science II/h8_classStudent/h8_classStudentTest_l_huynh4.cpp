/*
===========================================================================================
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
	3. You should have done the required changes in h8_classStudent.h before you come to 
		change this file. In this file, you need to add testing code in main() to test 
		the data member and the member functions you changed and added. Refer to the 
		sample output.
		1) Create student3 with the new constructor you added.
		2) Add two courses to student3 and print out her info.
		3) With student3, test deleteCourseByCRN(). Try to delete a course which doesn't 
			exist. And delete an existing one. Then print info of student3.
		4) Make sure you include the your h8_classStudent_yrlogin.h in this file.
	4. Add your code to wherever marked as "Your code below...". Please do not remove any 
		existing statements.
	5. Submit only the following two files. Name them properly as usual.
		h8_classStudent_yrlogin.h and h8_classStudentsTest_yrlgoin.cpp

Created: 	6/10/2012 by Jin Guo
Modified:	10/25/2017 by Jin Guo. Customized for Harper CSC122.
Modified:	3/31/2021 by Jin Guo. Significant changes for this semester.
===========================================================================================
*/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>	// for setw(), setprecision()
#include "h8_className.h"
#include "h8_classStudent_l_huynh4.h"

using namespace std;

int main()
{
	cout << "==============================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #8, Spring 2021\n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program implements Student class.\n";
	cout << "==============================================================\n\n";;

	cout << ">>> Create a student0 with default constructor ...\n";
	Student student0;
	cout << ">>> Create name1 with class FullName, then create student1 with the name ...\n";
	FullName name1("Jenny", "Lin");
	Student student1(name1);
	cout << ">>> Create student2 with first name, middle name and last name ...\n";
	Student student2("Bill", "Wright", "Washington");

	cout << "\n==> The Student objects just created: \n";
	student0.printInfo();
	student1.printInfo();
	student2.printInfo();

	cout << "\n>>> Resetting name of student0 ...\n";
	student0.setName("Marry", "White", "Saulter");
	cout << ">>> Adding a class to each student ...\n";
	student0.addCourse("Data Structure", "CSC2323");
	student1.addCourse("Discrete Math", "CSC1445");
	student2.addCourse("Artificial Intelligence", "CSC4225");

	cout << "\n==> After restring name and adding courses: \n";
	student0.printInfo();
	student1.printInfo();
	student2.printInfo();

	cout << "\n>>> Using a Student pointer to access member functions ...\n";
	cout << ">>> Adding more courses to student1 and student2 ...\n";
	Student *s_pt = &student1;
	s_pt->addCourse("Operating System", "CSC9363");
	s_pt = &student2;
	s_pt->addCourse("C++ Programming", "CSC1235");

	cout << "\n==> After using the pointer to add more courses: \n";
	student1.printInfo();
	student2.printInfo();

	cout << "\n>>> Finding if student2 take \"Artificial Intelligence\" ...\n";
	if (student2.findCourseByName("Artificial Intelligence") != -1)
		cout << "==> Yes, student2 took \"Artificial Intelligence\". \n";
	else
		cout << "==> No, student2 took \"Artificial Intelligence\". \n";

	cout << "\n>>>>>>>>>> Testing my code below <<<<<<<<<<\n\n";	
	/*
	==========================================================
	Add your testing code for the member functions you added.
	Refer to the sample output at the end of this file.

	<<<<<< Your code below... >>>>>
	==========================================================
	*/
	cout << ">>> Creating student3 with GPA ..." <<endl;
	Student student3("Anna", "De", "Groote", 3.85);

	cout << ">>> Adding courses to student3..." <<endl;
	student3.addCourse("Discrete Math", "CSC1445");
	student3.addCourse("C++ Programming", "CSC1235");

	cout << "==> The Student object just created: " << endl;
	student3.printInfo();
	cout << ">>> Deleting a course by ""CSC9999"" from student3 ..." << endl;
	student3.deleteCourseByCRN("CSC9999");
	student3.deleteCourseByCRN("CSC1445");

	cout << ">>> After deleting course(s) from student3 ..." << endl;
	student3.printInfo();
	cout << endl;
}

/* A Sample Output
==============================================================
Harper CSC122-S01 by Mr. Jin Guo: Assignment #8, Spring 2021
Student: <Your Name>

This program implements Student class.
==============================================================

>>> Create a student0 with default constructor ...
>>> Create name1 with class FullName, then create student1 with the name ...
>>> Create student2 with first name, middle name and last name ...

==> The Student objects just created:
-------------------------------------------
| Student: ,
| Courses taken: None
| GPA: 0.00
-------------------------------------------
-------------------------------------------
| Student: Lin, Jenny
| Courses taken: None
| GPA: 0.00
-------------------------------------------
-------------------------------------------
| Student: Wright, W. Bill
| Courses taken: None
| GPA: 0.00
-------------------------------------------

>>> Resetting name of student0 ...
>>> Adding a class to each student ...

==> After resetting name and adding courses:
-------------------------------------------
| Student: White, S. Marry
| Courses taken:
|   CSC2323: Data Structure
| GPA: 0.00
-------------------------------------------
-------------------------------------------
| Student: Lin, Jenny
| Courses taken:
|   CSC1445: Discrete Math
| GPA: 0.00
-------------------------------------------
-------------------------------------------
| Student: Wright, W. Bill
| Courses taken:
|   CSC4225: Artificial Intelligence
| GPA: 0.00
-------------------------------------------

>>> Using a Student pointer to access member functions ...
>>> Adding more courses to student1 and student2 ...

==> After using the pointer to add more courses:
-------------------------------------------
| Student: Lin, Jenny
| Courses taken:
|   CSC1445: Discrete Math
|   CSC9363: Operating System
| GPA: 0.00
-------------------------------------------
-------------------------------------------
| Student: Wright, W. Bill
| Courses taken:
|   CSC4225: Artificial Intelligence
|   CSC1235: C++ Programming
| GPA: 0.00
-------------------------------------------

>>> Finding if student2 take "Artificial Intelligence" ...
==> Yes, student2 took "Artificial Intelligence".

>>>>>>>>>> Testing my code below <<<<<<<<<<

>>> Creating student3 with GPA ...
>>> Adding courses to student3 ...

==> The Student object just created:
-------------------------------------------
| Student: Alice, M. Shirley
| Courses taken:
|   CSC2323: Data Structure
|   CSC1445: Discrete Math
| GPA: 3.50
-------------------------------------------

>>> Deleting a course by "CSC9999" from student3 ...
!!!Course CSC9999is not in the course list!!!

>>> Deleting a course by "CSC1445" from student3 ...
!!!Course CSC1445 was deleted!!!

>>> After deleting course(s) from student3 ...
-------------------------------------------
| Student: Alice, M. Shirley
| Courses taken:
|   CSC2323: Data Structure
| GPA: 3.50
-------------------------------------------

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

