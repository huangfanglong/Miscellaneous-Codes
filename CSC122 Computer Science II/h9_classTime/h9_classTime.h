/*
===============================================================================
Course: Harper 122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Operator Overloading
Program Description:
	This program defines a Time class and test it. The Time class maintains 
	time of the day. It is always positive in seconds ([0, 86400]) of one day
	and can be expressed in the format of hours:minutes:seconds.

Instructions:
	1. Study, understand and run the given program without any change. 
	2. Run h9_JG.out and your finished program should perform the same as this 
		one does.	
	3. You are required to overload some operators, which are listed in this file.
		Refer to s18_classPoint.cpp to find out how to overload such operators.
	4. Don't change anything in this h9_classTime.h, which is included by the
		two .cpp files. When you are done, just submit the following two files. 
		Please name them properly as usual:
			h9_classTime_yrlogin.cpp
			h9_classTimeTest_yrlogin.cpp 

Created:	5/5/2016 by Jin Guo. This was sample program.
Updated:	11/26/2017 by Jin Guo. Adapted the sample program to an assignment.
Updated:	4/7/2021 by Jin Guo. Significant improvements.
===============================================================================
*/
#pragma once // this will guarantee this .h to be included only once.

#include <iostream>	// for ostream
#include <string>	

using namespace std;

class Time
{
public:
	/**
	When a constructor has a negative value for seconds, minutes and hours, we do 
	counter-clock wise based on SECONDS_PER_DAY as modulus base.
	*/
	Time();						// default constructor with current local time.
	Time(int s);				// construct by the given seconds. s can be negative.
	Time(int h, int m, int s);	// h, m and s can be negative. 
	Time(const Time& t);		// copy constructor

	void setTime(int h, int m, int s);	// h, m and s can be negative.
	void setTime(int s);				// set by the given seconds. s can be negative.

	int secondsFrom(const Time& t2) const;	// find the difference between two times.
	string toString12Hour() const;			// print Time in format (HH:MM:SS AM/PM)
	string toString24Hour() const;			// print Time in format (HH:MM:SS)

	/**
	This function adds time by h, m and s and h, m and s can be any integer.
	h, m and s are converted to seconds, which is then modulo by SECONDS_PER_DAY.
	*/
	void addTime(int h, int m, int s);

	/**
	Set timer by the given time. h, m and s cannot be negative. When the given time
	expired, time alarm will set off.
	*/
	static void timeOut(int h, int m, int s);

	/*
	=========================================================================
	Please overload the following operators in your h9_classTime_yrlogin.cpp.
	You don't need to do any change in this file.
	=========================================================================
	*/
	// Overloading "<<" operator. Please use code of printFormat24Hour().
	friend ostream& operator<<(ostream& output, const Time&);

	// Notes: A friend function can modify private data members of the class.
	friend Time operator+(const Time&, const Time&);

	Time operator-(const Time&) const; // "-" operator, similar as "+". 
	bool operator==(const Time&) const; // check if two Time objects are the same.

private:
	int hour;	// 0 - 23 (24-hour clock format)
	int minute;	// 0 - 59
	int second;	// 0 - 59

	static const int SECONDS_PER_DAY = 86400; // = 60 * 60 * 24;
};

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

