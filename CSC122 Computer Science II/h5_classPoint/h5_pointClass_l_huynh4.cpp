/*
================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Point class
Program Description: This program defines and test class Point.

Instructions:
	This file should contain definitions of the class member functions declared
	but not defined in the declaration of class Poin in s18_classPoint.cpp, i.e.,
	the code after main(). See more instructions in h5_pointClass.h. 

Created: 6/28/2012 by Jin Guo
Updated: 11/18/2014 by Jin Guo. Customized for Harper.
Updated: 10/19/2017 by Jin Guo. Customized for CSC122.
Updated: 2/24/2021 by Jin Guo. Customized for this semester.
===============================================================================
*/
#include <iostream>
#include <string>
#include <cmath>	// for sqrt(), fabs()
#include <cfloat>	// for DBL_EPSILON : minimum double number

#include "h5_pointClass_l_huynh4.h" // change this to your h5_pointClass_yrlogin.h

using namespace std;

/**
============================================
Definitions of some Point member functions
============================================
*/

void Point::print(string p) const
{
	if (p.size())
		cout << p;
	cout << "(" << x << ", " << y << ")" << endl;
}

string Point::toString(string p) const
{
	string str;

	if (p.size())
		str = str + p;

	str = str + "(" + to_string(x) + ", " + to_string(y) + ")\n";

	return str;
}

void Point::resetXY(double new_x, double new_y)
{
	x = new_x;
	y = new_y;
}

void Point::move1(double a, double b)
{
	x += a;
	y += b;
}

Point& Point::move2(double a, double b)
{
	x += a;
	y += b;

	return (*this);
}

double Point::distanceTo(const Point& p2) const
{
	double xDiff = x - p2.x;
	double yDiff = y - p2.y;

	return sqrt(xDiff * xDiff + yDiff * yDiff);
}

/**
This is a friend function of Point class. It has direct access
to private members of Point class.
*/
double distanceOf2Points_v1(const Point& p1, const Point& p2)
{
	double xDiff = p1.x - p2.x;
	double yDiff = p1.y - p2.y;

	return sqrt(xDiff * xDiff + yDiff * yDiff);
}

/**
This is a regular function. It has access to private members
of Point class only via the class's public members.
*/
double distanceOf2Points_v2(const Point& p1, const Point& p2)
{
	double xDiff = p1.getX() - p2.getX();
	double yDiff = p1.getY() - p2.getY();

	return sqrt(xDiff * xDiff + yDiff * yDiff);
}

// This is a friend function of Point class.
ostream& operator<<(ostream& output, const Point& p)
{
	output << "(" << p.x << ", " << p.y << ")";
	return output;
}

// This is a friend function of Point class.
Point operator+(const Point& p1, const Point& p2)
{
	cout << "---> in friend +\n";

	return Point(p1.x + p2.x, p1.y + p2.y);
}

// This is a member function of Point class.
Point Point::operator+(const Point& p2)
{
	cout << "---> in member +\n";

	return Point(x + p2.x, y + p2.y);
}

Point Point::operator-(const Point& p2)
{
	return Point(x - p2.x, y - p2.y);
}

bool Point::operator==(const Point& p2) const
{
	return (fabs(x - p2.x) < 2 * DBL_EPSILON &&
		fabs(y - p2.y) < 2 * DBL_EPSILON);
}

const Point& Point::operator=(const Point& p2)
{
	if (this != &p2)
	{
		x = p2.x;
		y = p2.y;
	}

	return *this;
}
