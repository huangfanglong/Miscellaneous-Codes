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
	3. You are required to add code to test the overloaded operators. Refer to
		the sample output. Add your code wherever is marked "Your code below ...". 
	4. Don't change anything in h9_classTime.h. When you are done, just submit the 
		following two files. Please name them properly as usual:
			h9_classTime_yrlogin.cpp
			h9_classTimeTest_yrlogin.cpp 

Created:	5/5/2016 by Jin Guo. This was sample program.
Updated:	11/26/2017 by Jin Guo. Adapted the sample program to an assignment.
Updated:	4/7/2021 by Jin Guo. Significant improvements.
===============================================================================
*/
#include <iostream>
#include "h9_classTime.h"

using namespace std;

int main()
{
	cout << "===================================================================\n";
	cout << "Harper 122-S01 by Mr. Jin Guo: Assignment #9, Spring 2021 \n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program defines a Time class with some operators overloaded.\n";
	cout << "===================================================================\n\n";

	Time t0;
	cout << ">>> Construct t0 with default constructor ...\n";
	cout << "t0: " << t0.toString24Hour() << " | " << t0.toString12Hour() << endl;

	t0.setTime(17, 27, 6);	// change time
	cout << "--> After t0.setTime(17, 27, 6) ...\n";
	cout << "t0: " << t0.toString24Hour() << " | " << t0.toString12Hour() << endl; 

	Time t1;
	cout << "\n>>> Construct t1 with default constructor ...\n";
	cout << "t1: " << t1.toString24Hour() << " | " << t1.toString12Hour() << endl;	
	t1.setTime(11, 59, 30);
	cout << "--> After t1.setTime(11, 59, 30) ...\n";
	cout << "t1: " << t1.toString24Hour() << " | " << t1.toString12Hour() << endl;
	t1.setTime(-90);
	cout << "--> After t1.setTime(-90) ...\n";
	cout << "t1: " << t1.toString24Hour() << " | " << t1.toString12Hour() << endl;

	Time t2(4, 5, 34);
	cout << "\n>>> Construct t2: Time t2(4, 5, 34) ...\n";
	cout << "t2: " << t2.toString24Hour() << " | " << t2.toString12Hour() << endl;
	t2.addTime(2, 3, 4);
	cout << "--> After t2.addTime(2, 3, 4) ...\n";
	cout << "t2: " << t2.toString24Hour() << " | " << t2.toString12Hour() << endl;

	Time t3(t2);
	cout << "\n>>> Time t3 is cloned from t2 ...\n";
	cout << "t3: " << t3.toString24Hour() << " | " << t3.toString12Hour() << endl;
	t3.addTime(0, 1, 30);
	cout << "--> After t3.addTime(0, 1, 30) ...\n";
	cout << "t3: " << t3.toString24Hour() << " | " << t3.toString12Hour() << endl;
	cout << "--> The time difference from t3 to t2 is: "
		<< t3.secondsFrom(t2) << " seconds.\n";

	t3.addTime(0, -1, -30);
	cout << "--> After t3.addTime(0, -1, -30) ...\n";
	cout << "t3: " << t3.toString24Hour() << " | " << t3.toString12Hour() << endl;
	cout << "--> The time difference from t3 to t2 is: "
		<< t3.secondsFrom(t2) << " seconds.\n";	

	cout << "\n>>> Set an alarm in 3 seconds ...\n";
	Time::timeOut(0, 0, 3);

	cout << "\n=============================================================";
	cout << "\nMy code to test overloaded operators <<, - , + and == ...";
	cout << "\n=============================================================\n\n";
	/*
	=============================================================================
	Please add code below to test the overloaded operators. You should re-use the 
	above objects. Since "<<" is overloaded, use "<<" for all of your 
	Time output. Please imitate the sample output at the end of this file.
	
	<<<<<< Your code below... >>>>>
	=============================================================================
	*/
	cout << ">>> Test t1 + t2..." << endl;
	cout << "t1:      " << t1 << endl;
	cout << "t2:      " << t2 << endl;
	cout << "t1 + t2: " << t1 + t2 << endl << endl;

	cout << ">>> Test t1 - t2..." << endl;
	cout << "t1:      " << t1 << endl;
	cout << "t2:      " << t2 << endl;
	cout << "t1 - t2: " << t1 - t2 << endl << endl;

	cout << ">>> Test if two Time objects are the same..." << endl;
	cout << ((t1 == t2) ? "t1 and t2 are the same!" : "t1 and t2 are different!") << endl << endl;;

	cout << endl;
}

/* A Sample Output
===================================================================
Harper 122-S01 by Mr. Jin Guo: Assignment #9, Spring 2021
Student: <Your Name>

This program defines a Time class with some operators overloaded.
===================================================================

>>> Construct t0 with default constructor ...
t0: 19:15:37 | 07:15:37 PM
--> After t0.setTime(17, 27, 6) ...
t0: 17:27:06 | 05:27:06 PM

>>> Construct t1 with default constructor ...
t1: 19:15:37 | 07:15:37 PM
--> After t1.setTime(11, 59, 30) ...
t1: 11:59:30 | 11:59:30 AM
--> After t1.setTime(-90) ...
t1: 23:58:30 | 11:58:30 PM

>>> Construct t2: Time t2(4, 5, 34) ...
t2: 04:05:34 | 04:05:34 AM
--> After t2.addTime(2, 3, 4) ...
t2: 06:08:38 | 06:08:38 AM

>>> Time t3 is cloned from t2 ...
t3: 06:08:38 | 06:08:38 AM
--> After t3.addTime(0, 1, 30) ...
t3: 06:10:08 | 06:10:08 AM
--> The time difference from t3 to t2 is: 90 seconds.
--> After t3.addTime(0, -1, -30) ...
t3: 06:08:38 | 06:08:38 AM
--> The time difference from t3 to t2 is: 0 seconds.

>>> Set an alarm in 3 seconds ...
Time is up!!!

=============================================================
My code to test overloaded operators <<, - , + and == ...
=============================================================

>>> Test t1 + t2 ...
t1:      23:58:30
t2:      06:08:38
t1 + t2: 06:07:08

>>> Test t1 - t2 ...
t1:      23:58:30
t2:      06:08:38
t1 - t2: 17:49:52

>>> Test if two Time objects are same ...
t1 and t2 are different!
t2 and t3 are the same!

*/

/*
************************************************
* (C) Copyright - by Jin Guo
*
* This program is free for my class students.
* For any other purpose of using this program,
* please ask for permisson by sending email to:
* taiji.guo@gmail.com
************************************************
*/

