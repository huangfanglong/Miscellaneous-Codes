/*
=====================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Stack Class Template  
Program Description:
	This program demonstrates how to implement a stack data structure with class
	template.

Instructions:
	1. First try to understand the given program well before you add your code.  
	2. Run h13_JG.out which is how your finished program should perform. Imitate 
		its prompts and output as precisely as you can.
	3. Add your code to wherever marked as "Your code below...". You don't need to 
		add or delete any statements in this file. You only need to comment out and 
		uncomment some lines. 
	4. When you are done, submit your two files:
		h13_stackTemplate_yrlogin.h
		h13_stackTemplateTest_yrlogin.cpp 

Created: 	6/10/2012 by Jin Guo
Updated:	12/3/2017 by Jin Guo. Customized for Harper CSC122.
Updated:	5/4/2021 by Jin Guo. Adapted for this semester. Some improvements.
=====================================================================================
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream> // for istringstream
#include "h13_stackTemplate_l_huynh4.h"

using namespace std;

int main()
{
	cout << "===============================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #13, Spring 2021\n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program defines and tests stack template class.\n";
	cout << "===============================================================\n\n";;

	/*
	================================================================
	To test your stack template, comment out lines 57, 77 and
	uncomment lines 58, 78, 94-107.

	<<<<<< Your code below... >>>>>
	=================================================================
	*/

	//----------------------------------------------------------------
	cout << ">>>> Testing CharStack or Stack<char> >>>>\n";

	char str[] = "Nothing is perfect!";

	//CharStack stack1;
	Stack<char> stack1;

	cout << "\nPush string \"Nothing is perfect!\" into stack1 ...\n";
	for (size_t i = 0; !stack1.isFull() && i < strlen(str);)
		stack1.pushTop(str[i++]);

	cout << "Number of elements in stack1: " << stack1.getElementNum() << "\n";

	cout << "\nPop out the content in stack1 ...\n";
	char c;
	while (stack1.popTop(c))
		cout << c;
	cout << "\n----------------------------------------------------------------\n\n";

	cout << ">>>> Testing doubleStack or Stack<double> >>>>\n";

	vector<double> V { 10.1, 11.2, 22.3, 33.4, 44.5 };
	int size = V.size();

	//DoubleStack stack2(size);
	Stack<double> stack2(size);

	cout << "\nPush double numbers {10.1, 11.2, 22.3, 33.4, 44.5} into stack2 ...\n";
	for (int i = 0; !stack2.isFull() && i < size;)
		stack2.pushTop(V[i++]);

	cout << "Number of elements in stack2: " << stack2.getElementNum() << "\n";

	cout << "\nPop out the content in stack2 ...\n";
	double x;
	while (stack2.popTop(x))
		cout << x << " ";
	cout << "\n----------------------------------------------------------------\n\n";

	cout << ">>>> Testing Stack<string> >>>>\n";

	istringstream iss("Four score and seven year ago");

	Stack<string> stack3;

	cout << "\nPush sentence \"Four score and seven year ago\" into stack3 ...\n";
	string word; 
	while (!stack3.isFull() && iss >> word)
		stack3.pushTop(word);
	cout << "Number of elements in stack3: " << stack3.getElementNum() << "\n";

	cout << "\nPop out the content in stack3...\n";
	while (stack3.popTop(word))
		cout << word << " ";
	cout << "\n----------------------------------------------------------------\n";

	cout << endl;
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

