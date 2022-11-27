#ifndef POINTCLASS_H
#define POINTCLASS_H
/*
================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Point class
Program Description: This program defines and tests class Point. Study the 
	structure of this program and the dicussions in the comment header. You should 
	review what you learned about C++ class in CSC121 and learn some new concepts
	and constructs from this program. By studying this program, make sure you 
	understand the following:
		*) Declare/define a class, use a class to create its objects.
		*) Use class member functions with its objects.
		*) Class constructors: default/copy/regular constructor. 
		*) Private/public members.
		*) Operator overloading.
		*) Friend function of a class.
		*) "this" pointer.
		*) Call by constant reference.
		*) inline function.

Instructions: 
	1. Compile and run the given program s18_classPoint.cpp without any change. 
	2. Your job is to split s18_classPoint.cpp into three files:
		1) h5_pointClass_yrlogin.h: it should contain only class declaration
		   and the inline functions.
		2) h5_pointClass_yrlogin.cpp: it should contain all definitions of
		   the class member functions not defined in the .h file. 
		3) h5_pointClassTest_yrlogin.cpp: it should contain the main() function
		   of the testing code. 
	3. If you want to compile this program on Unix/ares, put the above three files in
		one dir and do as follows:
			$ g++ h5*.cpp
	4. Submit the above three files. Name your files properly as usual. 

Notes: 
	1. If a member function is defined within the class declaration, it's defined 
		as "inline" by default. The general rule is that if a function has only one 
		statement, it can be defined within the class. Otherwise it should be 
		defined outside of the class after main().
	2. Put the inline functions defined outside of the class declaration into your
		.h file.
	3. For each file, include ONLY the libraries which are needed for that file.

Created: 6/28/2012 by Jin Guo
Updated: 11/18/2014 by Jin Guo. Customized for Harper.
Updated: 10/19/2017 by Jin Guo. Customized for CSC122.
Updated: 2/24/2021 by Jin Guo. Customized for this semester.
===============================================================================
*/

#include <iostream>
#include <string>

using namespace std;

class Point
{
	/**
	This is a friend function of this Point class. It has direct access
	to private members of this class.
	*/
	friend double distanceOf2Points_v1(const Point& p1, const Point& p2);

	// Overloading "<<" operator.
	friend ostream& operator<<(ostream& output, const Point& p);

	// Overloading "+" operator.
	friend Point operator+(const Point& p1, const Point& p2);

public:
	// Constructors
	Point() : x(0.0), y(0.0) {} // default constructor
	Point(double new_x, double new_y) : x(new_x), y(new_y) {}
	Point(const Point& p) : x(p.x), y(p.y) {} // copy constructor

	// Accessors
	double getX() const { return x; };
	double getY() const { return y; };
	void print(string p = "") const;		// in format of "p(x, y)"
	string toString(string p = "") const;	// in format of "p(x, y)"

	// Mutators
	void resetX(double new_x = 0.0) { x = new_x; };
	void resetY(double new_y = 0.0) { y = new_y; };
	void resetXY(double new_x = 0.0, double new_y = 0.0);

	// Utilities
	Point add(const Point& p2) const;	// addition of two points
	Point sub(const Point& p2) const;	// subtraction of two points
	void move1(double a, double b);		// move without returning current object.
	Point& move2(double a, double b);	// move and return current object.
	double distanceTo(const Point& p2) const;  // distance between two points	

	// Overloading of operators
	Point operator+(const Point& p2);
	Point operator-(const Point& p2);
	bool operator==(const Point& p2) const;
	const Point& operator=(const Point& p2);

private:
	double x;
	double y;
};

double distanceOf2Points_v2(const Point& p1, const Point& p2);

inline
Point Point::add(const Point& p2) const
{
	return Point(x + p2.x, y + p2.y);
}

inline
Point Point::sub(const Point& p2) const
{
	return Point(x - p2.x, y - p2.y);
}

#endif


