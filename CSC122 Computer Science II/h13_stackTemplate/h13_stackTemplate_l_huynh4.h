#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H
/*
====================================================================================
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
	3. You need to modify this .h file to add the stack class template. Add it to
		wherever marked as "Your code below...". Please do not remove any existing 
		statements.
	4. After you added your code for the template, you need to test your code
		in main() of h13_stackTemplateTest_yrlogin.cpp. Read the instructions in
		h13_stackTemplateTest.cpp.
	5. When you are done, submit your two files:
		h13_stackTemplate_yrlogin.h
		h13_stackTemplateTest_yrlogin.cpp 

Created: 	6/10/2012 by Jin Guo
Updated:	12/3/2017 by Jin Guo. Customized for Harper CSC122.
Updated:	5/4/2021 by Jin Guo. Adapted for this semester. Some improvements.
=====================================================================================
*/
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

static const int STACK_MAX_SIZE = 100; // default size.

//===============================================================
class CharStack
{
public:
	CharStack(int n = STACK_MAX_SIZE);	// constructor.
	~CharStack() { delete[] stack; }	// destructor.

	bool popTop(char& topElem);			// pop out the top element.
	bool pushTop(const char& newElem);	// push in a new element.
	bool peekTop(char& topElem) const;	// return the top element.

	void reset() { top = -1; }
	bool isEmpty() const { return (top == -1); }
	bool isFull() const { return (top == size - 1); }
	int getElementNum() const { return top + 1; }
	int getStackSize() const { return size; }

private:
	int size;		// size of stack.
	char* stack;	// pointer of stack memory.
	int top;		// points to the top element, -1 means the stack is empty.
};

CharStack::CharStack(int n)
{	
	size = (n > 0 && n < STACK_MAX_SIZE) ? n : STACK_MAX_SIZE;
	top = -1;
	stack = new char[size];
}

bool CharStack::popTop(char& topElem)
{
	if (!isEmpty())
	{
		topElem = stack[top--];
		return true;
	}

	return false;
}

bool CharStack::pushTop(const char& newElem)
{
	if (!isFull())
	{
		stack[++top] = newElem;
		return true;
	}

	return false;
}

bool CharStack::peekTop(char& topElem) const
{
	if (!isEmpty())
	{
		topElem = stack[top];
		return true;
	}

	return false;
}

//===============================================================
class DoubleStack
{
public:
	DoubleStack(int n = STACK_MAX_SIZE);	// constructor.
	~DoubleStack() { delete[] stack; }		// destructor.

	bool popTop(double& topElem);			// pop out the top element.
	bool pushTop(const double& newElem);	// push in a new element.
	bool peekTop(double& topElem) const;	// return the top element.

	void reset() { top = -1; }
	bool isEmpty() const { return (top == -1); }
	bool isFull() const { return (top == size - 1); }
	int getElementNum() const { return top + 1; }
	int getStackSize() const { return size; }

private:
	int size;		// size of stack.
	double* stack;	// pointer of stack memory.
	int top;		// points to the top element, -1 means the stack is empty.
};

DoubleStack::DoubleStack(int n)
{
	size = (n > 0 && n <= STACK_MAX_SIZE) ? n : STACK_MAX_SIZE;
	top = -1;
	stack = new double[size];
}

bool DoubleStack::popTop(double& topElem)
{
	if (!isEmpty())
	{
		topElem = stack[top--];
		return true;
	}

	return false;
}

bool DoubleStack::pushTop(const double& newElem)
{
	if (!isFull())
	{
		stack[++top] = newElem;
		return true;
	}

	return false;
}

bool DoubleStack::peekTop(double& topElem) const
{
	if (!isEmpty())
	{
		topElem = stack[top];
		return true;
	}

	return false;
}

/*
==============================================================
Add your code to define stack template. You may copy the code
of CharStack and then replace Char with T.

<<<<<< Your code below... >>>>>
==============================================================
*/
template <class T>
class Stack
{
public:
	Stack<T>(int n = STACK_MAX_SIZE);	// constructor.
	~Stack<T>() { delete[] stack; }		// destructor.

	bool popTop(T& topElem);			// pop out the top element.
	bool pushTop(const T& newElem);	// push in a new element.
	bool peekTop(T& topElem) const;	// return the top element.

	void reset() { top = -1; }
	bool isEmpty() const { return (top == -1); }
	bool isFull() const { return (top == size - 1); }
	int getElementNum() const { return top + 1; }
	int getStackSize() const { return size; }

private:
	int size;		// size of stack.
	T* stack;	// pointer of stack memory.
	int top;		// points to the top element, -1 means the stack is empty.
};

template <class T>
Stack<T>::Stack(int n)
{
	size = (n > 0 && n <= STACK_MAX_SIZE) ? n : STACK_MAX_SIZE;
	top = -1;
	stack = new T[size];
}

template <class T>
bool Stack<T>::popTop(T& topElem)
{
	if (!isEmpty())
	{
		topElem = stack[top--];
		return true;
	}

	return false;
}

template <class T>
bool Stack<T>::pushTop(const T& newElem)
{
	if (!isFull())
	{
		stack[++top] = newElem;
		return true;
	}

	return false;
}

template <class T>
bool Stack<T>::peekTop(T& topElem) const
{
	if (!isEmpty())
	{
		topElem = stack[top];
		return true;
	}

	return false;
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
#endif

