/*
======================================================================================
Course: Harper CSC121-122

Program Name: Point class
Program Description:
	This program defines Point class. New constructs such as friend function, 
	inline function, overloaded function/operator and "this" pointer are introduced.

Discussion:
	1.The operator+ can be either a friend function or a member function. Which is
		preferred? Whenever we can, choose a member function to overload an operator.
		Sometimes we have to use a non-member function and have to make this 
		non-member function to be a friend if it needs to access the private 
		members of the class. When both a member function and a non-member function
		are used to overload operator+, as I tried here, the member function is
		picked up. 

		One advantage of a non-member version is that it can "coerce" the first 
		parameter while a member function obviously cannot.

	2. It's very tricky to compare two double numbers to see if they are the same. 
		Because of the hardware representation of the smallest floating number, 
		two variables of a floating type with the same value, e.g, x = 2.5 and 
		y = 2.5, may result in inequality between them. Within a computer, x and y
		may be represented as x = 2.5000...01 and y = 2.4999...9. Thus, 
		"return (x == y);" may return a false value. That's why DBL_EPSILON as 
		the smallest floating number is introduced here to compare two float numbers 
		to check if they are the same. If |x - y| is small enough, we think that they 
		the same.

	3. A function is defined within its class declaration is an "inline" function 
		by default. You may define a function outside the class declaration and 
		use keyword "inline" to make it to be inline. An inline function is 
		hard-coded within the client code thus function calling overhead can be
		avoided. However, an inline function is not guaranteed. The keyword "inline"
		is just a suggestion to compiler. Note that an inline function outside of
		a class	can only be defined within the same file where the class is declared.
	
	4. When overloading assignment operator "=", different versions may have some 
		subtle differences. Note that associativity of = is from right to left. So,
		p1 = p2 = p3 is the same as p1 = (p2 = p3).
		1) void operator=(const Point& p2);
			p1 = p2 = p3 is not allowed with this version. You can only do p1 = p2.
		2) Point operator=(const Point& p2);
			This allows p1 = p2 = p3, where (p2 = p3) returns a new object, not p2 itself!
			The copy constructor in the definition will be invoked implicitly.
		3) Point& operator=(const Point& p2);
			This is a common version. You can do p1 = p2 = p3, where (p2 = p3) return p2.
			But this also allows (p1 = p2) = p3, which doesn't make sense. 
		4) const Point& operator=(const Point& p2);
			Finally, this version is the best. You can do p1 = p2 = p3, 
			where (p2 = p3) return p2. But if you do (p1 = p2) = p3 or 
			(p1 = p2).move1(1.0, 1.0), you will get compiling error!

Created: 6/28/2012 by Jin Guo
Updated: 10/14/2017 by Jin Guo. Added more member functions.
Updated: 11/17/2017 by Jin Guo. Added friend function version of overloaded
			operator+ and discussions.
Updated: 10/12/2018 by Jin Guo. Added Item 3 in the above Discussion.
Updated: 2/26/2020 by Jin Guo. Improved some member functions. 
			Operator"=" was overloaded.
Updated: 2/27/2020 by Jin Guo. For distanceOf2Points_v1(), change the p1, p2
			to be constant reference. Change <math.h> to be <cmath>.
Updated: 2/24/2021 by Jin Guo. Added toString(), discussion about overloading 
			assignment operator plus other improvements.
======================================================================================
*/
#include <iostream>
#include <string>
#include <cmath>	// for sqrt(), fabs()
#include <iomanip>	// for fixed, setprecision()
#include <cfloat>	// for DBL_EPSILON : minimum double number

using namespace std;

/**
===================================================================
Class Point declaration including some inline function definitions.
===================================================================
*/
class Point
{
	/**
	This is a friend function of this Point class. It has direct access
	to private members of this class.	
	*/
	friend double distanceOf2Points_v1(const Point& p1, const Point& p2);

	// Overloading "<<" operator.
	friend ostream &operator<<(ostream &output, const Point& p);

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

/**
This is a regular function. It has access to private members
of Point class only via the class's public members.
*/
double distanceOf2Points_v2(const Point& p1, const Point& p2);

/**
=====================================
main() function to test class Point.
=====================================
*/
int main()
{
	// Print header.
	cout << "=======================================================\n";
	cout << "SHarper CSC121-122 by Mr. Jin Guo: Sample Program 18\n\n";
	cout << "This program defines and test class Point.\n";
	cout << "========================================================\n\n";

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

