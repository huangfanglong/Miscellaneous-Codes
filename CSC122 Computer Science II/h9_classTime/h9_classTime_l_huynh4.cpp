/*
===================================================================================
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
	3. You are required to overload some operators. Add your code wherever 
		is marked "Your code below ...". Refer to s18_classPoint.cpp to find out
		how to overload such operators.
	4. Don't change anything in h9_classTime.h. When you are done, just submit the 
		following two files. Please name them properly as usual:
			h9_classTime_yrlogin.cpp
			h9_classTimeTest_yrlogin.cpp 

Created:	5/5/2016 by Jin Guo. This was sample program.
Updated:	11/26/2017 by Jin Guo. Adapted the sample program to an assignment.
Updated:	4/7/2021 by Jin Guo. Significant improvements.
===================================================================================
*/
#define _CRT_SECURE_NO_WARNINGS // in order to use localtime() in VC++

#include <iostream>
#include <sstream>		// for ostringstream
#include <iomanip>		// for setfill, setw
#include <cassert>		// for assert()
#include <ctime>		// for struct tm, time_t, time(), localtime()
#include "h9_classTime.h"

using namespace std;

/**
This default constructor construct a time object of current local time 
with time(0).
*/
Time::Time()
{
	time_t now;
	time(&now);		// get the current time in seconds
	//now = time(0);	// get the current time in seconds

	struct tm t = *localtime(&now);			// get the local time.
	//struct tm& t = *localtime(&now);		// use reference to avoid a copy.
	//const struct tm& t = *localtime(&now);	// use const reference.
	//tm& t = *localtime(&now);				// omit keyword struct.

	hour = t.tm_hour;
	minute = t.tm_min;
	second = t.tm_sec;
}

Time::Time(int s) {	setTime(s); }

Time::Time(int h, int m, int s) { setTime(h, m, s); }

Time::Time(const Time& t)
{
	hour = t.hour;
	minute = t.minute;
	second = t.second;
}

void Time::setTime(int s)
{
	int curSeconds; // current seconds.

	if (s >= 0)
		curSeconds = s % SECONDS_PER_DAY; // get the remainder.
	else // turn negative seconds to positive by its complement.
		curSeconds = SECONDS_PER_DAY + s % SECONDS_PER_DAY;

	hour = curSeconds / 3600;
	minute = (curSeconds % 3600) / 60;
	second = curSeconds % 60;
}

void Time::setTime(int h, int m, int s)
{
	int totalSeconds;
	totalSeconds = h * 3600 + m * 60 + s;

	setTime(totalSeconds);
}

int Time::secondsFrom(const Time& t) const
{
	int s1 = hour * 3600 + minute * 60 + second;
	int s2 = t.hour * 3600 + t.minute * 60 + t.second;

	return (s1 - s2);
}

void Time::addTime(int h, int m, int s)
{
	int t0, t1;

	t0 = hour * 3600 + minute * 60 + second; // this time.
	t1 = h * 3600 + m * 60 + s; // time passed in.

	if (t1 >= 0)
		t1 = t1 % SECONDS_PER_DAY;
	else // turn negative seconds to positive by its complement.
		t1 = SECONDS_PER_DAY + t1 % SECONDS_PER_DAY;

	t0 = t0 + t1;
	setTime(t0);
}

void Time::timeOut(int h, int m, int s)
{
	assert(h >= 0 && m >= 0 && s >= 0);

	int seconds = h * 3600 + m * 60 + s;
	Time start;

	while (Time().secondsFrom(start) < seconds)
		;

	cout << "Time is up!!!\a\a\a\n";
}

string Time::toString12Hour() const
{
	ostringstream output;

	output << setfill('0') << setw(2)
		<< ((hour == 12) ? 12 : hour % 12) << ":"
		<< setw(2) << minute << ":" << setw(2) << second
		<< (hour < 12 ? " AM" : " PM");

	return output.str();
}

string Time::toString24Hour() const
{
	ostringstream output;

	output << setfill('0') << setw(2) << hour << ":"
		<< setw(2) << minute << ":" << setw(2) << second;

	return output.str();
}

/*
===================================================================
Please define the overloaded operators within Time class
declaration in h9_classTime.h. Uncomment the following code and add
your code in the function body.

<<<<<< Your code below ... >>>>>
===================================================================
*/


ostream& operator<<(ostream& output, const Time& t)
{
	output << setfill('0') << setw(2) << t.hour << ":" 
		<< setw(2) << t.minute << setw(2) << ":" << t.second;
	return output;
}

Time operator+(const Time& t1, const Time& t2)
{
	return Time(t1.hour + t2.hour, t1.minute + t2.minute, t1.second + t2.second);
}

Time Time::operator-(const Time& t) const
{
	return Time(hour - t.hour, minute - t.minute, second - t.second);
}

bool Time::operator==(const Time& t) const
{
	return (hour == t.hour && minute == t.minute && second == t.second);
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

