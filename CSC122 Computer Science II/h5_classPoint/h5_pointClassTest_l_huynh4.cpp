/*
================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Point class
Program Description: This program defines and test class Point.

Instructions:
	This file should contain the testing code of the class, i.e., the main() of
	s18_classPoint.cpp. See more instructions in h5_pointClass.h. 

Created: 6/28/2012 by Jin Guo
Updated: 11/18/2014 by Jin Guo. Customized for Harper.
Updated: 10/19/2017 by Jin Guo. Customized for CSC122.
Updated: 2/24/2021 by Jin Guo. Customized for this semester.
===============================================================================
*/
#include <iostream>
#include <string>
#include <iomanip>	// for fixed, setprecision()
#include "h5_pointClass_l_huynh4.h" // change this to your h5_pointClass_yrlogin.h

using namespace std;

/**
========================================
The main() function to test class Point.
========================================
*/

int main()
{
	// Print header.
	cout << "================================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #1, Spring 2021\n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program defines and test class Point.\n";
	cout << "================================================================\n\n";

	cout << fixed << setprecision(2); // set format of printing a double number

	cout << ">>> Testing constructors ...\n";
	cout << "p1: use default constructor Point p1\n";
	cout << "p2: use regular constructor Point p2(4.0, 2.0)\n";
	cout << "p3: use copy constructor Point p3(p2)\n\n";

	Point p1;
	Point p2(4.0, 2.0);
	Point p3(p2);

	cout << ">>> Testing print(), toString() and overloaded \"<<\" ...\n";
	p1.print("p1");
	cout << p2.toString("p2");
	cout << "p3" << p3 << "\n";

	cout << "\n>>> Testing getX() and getY() ...\n";
	cout << "x-coordinate of p2: " << p2.getX() << endl;
	cout << "y-coordinate of p2: " << p2.getY() << endl;
	cout << "\n";

	cout << ">>> p1.resetX(2.3), p1.resetY(3.4), p1.resetXY(5.0, 5.0) ...\n";
	p1.resetX(2.3);
	p1.print("p1");
	p1.resetY(3.4);
	p1.print("p1");
	p1.resetXY(5.0, 5.0);
	p1.print("p1");
	cout << "\n";

	cout << ">>> Testing p1.add(p2) and p1.sub(p2) ...\n";
	p1.print("p1");
	p2.print("p2");
	cout << "p1.add(p2) = " << p1.add(p2) << "\n";
	cout << "p1.sub(p2) = " << p1.sub(p2) << "\n\n";

	cout << ">>> Moving p3 by (3.0, 3.0) with move1() ...\n";
	cout << "p3" << p3 << " --> ";
	p3.move1(3.0, 3.0);
	cout << "p3" << p3 << "\n";

	cout << "\n>>> Moving p3 by (3.0, 4.0) with move2() ...\n";
	cout << "p3" << p3 << " --> p3";
	p3.move2(3.0, 4.0).print();
	cout << "\n";

	Point p4(5.3, 6.2);
	cout << ">>> Find distance between p3 and p4 by member function:  "
			<< p3.distanceTo(p4) << endl;
	cout << ">>> Find distance between p3 and p4 by friend function:  "
			<< distanceOf2Points_v1(p3, p4) << endl;
	cout << ">>> Find distance between p3 and p4 by regular function: "
			<< distanceOf2Points_v2(p3, p4) << endl;

	cout << "\n>>> Testing overloaded operators ...\n";
	cout << "p1" << p1 << " + " << "p2" << p2 << " = " << p1 + p2 << endl;
	cout << "p1" << p1 << " - " << "p2" << p2 << " = " << p1 - p2 << endl;
	cout << "p1" << p1 << " == " << "p2" << p2 << "? ";
	cout << ((p1 == p2) ? "Yes!" : "No!") << "\n";

	cout << "\nAfter p4 = p3, \n";
	p4 = p3;
	cout << "p4" << p4 << " == " << "p3" << p3 << "? ";
	cout << ((p4 == p3) ? "Yes!" : "No!") << "\n\n";

	return 0;

}

