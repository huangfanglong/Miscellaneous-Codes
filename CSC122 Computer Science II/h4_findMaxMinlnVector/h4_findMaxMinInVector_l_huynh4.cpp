//Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
//Student Name: Long Huynh

//Program Name: Exercises on vector and C-ArrayprintInt_C_Array
//Program Description:
	//This assignment gives you some exercises about vector and array with functions 
	//such as filling in data, printing out data and finding sum, etc. Students
	//are required to understand the differences between using array and vector.

//Instructions:
	//1. Try to understand and run this program before you do any change.
	//2. h4_JG.out is the finished executable	for Unix. When you are done, your 
		//program should perform the same as this one does. 
	//3. You need to define some given function declarations.
	//4. Add your code to wherever marked as "Your code below...". Please do
		//not remove any existing statements.
	//5. Submit only your .cpp file and name it properly as usual.

//Created: 10/8/2017 by Jin Guo
//Updated: 8/21/2018 by Jin Guo. Adapted for CSC122.
//Updated: 2/23/2020 by Jin Guo. Adapted for this semester.
//=====================================================================================
//*/
#include <iostream>		// for cin, cout, fixed
#include <iomanip>		// for setw(), setprecision()
#include <cstdlib>		// for srand(), rand()
#include <ctime>		// for time() as a seed for srand()
#include <algorithm>	// std::swap()
#include <vector>

using namespace std;

// Some functions for C++ vector
void randomIntVector(vector<int>& A);		// fill in random numbers for A.
int sumOfIntVector(const vector<int>& A);	// find sum of A.
void printIntVector(const vector<int>& A);	// print A.

// Some functions for C-Array
void randomInt_C_Array(int* A, size_t size);		// fill in random numbers for A.
int sumOfInt_C_Array(const int* A, size_t size);	// find sum of A.
void printInt_C_Array(const int* A, size_t size);		// print A.

/*
=================================================================++++======
<<<<<< Your code below... >>>>>
Your are required to define the following three functions after main().
Uncomment the corresponding lines in main() after you defined the functions.
============================================================================
*/

/*	
This function will find maximum and minimum with their indexes		 
for a given integer vector.

@param A: the vector we need to find its maximum and minimum.
@param max: used to return the maximum.
@param min: used to return the minimum.
@param max_i; used to return the index of maximum.
@param min_i; used to return the index of minimum.
*/
void findMinMaxIntVector(const vector<int>& A, int& max, int& max_i, int& min, int& min_i);

/*
This function will calculate the average of a C-Array.

@param A: the array to find its average.
@param size: the size of A. 
return: the average of A.
*/
double averageInt_C_Array(const int* A, size_t size);	
	
static const size_t SIZE = 9;	// set size of the vector

int main()
{
	// Print header.
	cout << "================================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #4, Spring 2021 \n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program will fill in data for a C-array or a C++ vector,\n";
	cout << "find the sum, maximum and minimum elements and average.\n";
	cout << "================================================================\n\n";

	srand((int)time(0));	// seed the rand() by using the time function.

	vector<int> A(SIZE);	// declare vector A with SIZE, initialized with 0.
	
	cout << ">>> Generate some random numbers for vector A ...\n";
	randomIntVector(A);
	printIntVector(A);

	cout << "\n>>> Find the sum of all elements in this vector ...\n";
	cout << "The sum is: " << sumOfIntVector(A) << endl;

	cout << "\n>>> Find the maximum and minimum values in this vector...\n";
	int max, min, max_i, min_i;	// for max/min values and their indexes
	max = min = A[0];
	max_i = min_i = 0;

	// Uncomment the following statement after you defined findMinMaxIntVector().
	findMinMaxIntVector(A, max, max_i, min, min_i);
	cout << "The maximum value is: A[" << max_i << "] = " << max << "\n";
	cout << "The minimum value is: A[" << min_i << "] = " << min << "\n\n";
	 
	cout << "============================================\n";
	cout << "The following code is for integer array...\n";
	cout << "============================================\n";

	//size_t size = 10; // the size may come from keyboard.
	int* B = new int[SIZE]; // dynamically allocate the array memory.

	cout << "\n>>> Fill in some randdom numbers for array B ...\n";
	randomInt_C_Array(B, SIZE);
	printInt_C_Array(B, SIZE);

	cout << "\n>>> Find the sum of all elements in this vector ...\n";
	cout << "The sum is: " << sumOfInt_C_Array(B, SIZE) << endl;

	cout << fixed << setprecision(2);
	cout << "\n>>> Find the average of B ...\n";
	// Uncomment the following statement after you defined averageIntArray().
	cout << "The average: " << averageInt_C_Array(B, SIZE) << "\n\n";

	delete[] B;	// release the memory allocated by new operator.

	return 0; 
}

//====================================================

// The function definitions for C++ vector
void randomIntVector(vector<int>& A)
{
	size_t SIZE = A.size();
	for (size_t i = 0; i < SIZE; ++i)
		A[i] = 1 + (rand() + i) % (SIZE * 10); // this reduces duplicates.
}

int sumOfIntVector(const vector<int>& A)
{
	int sum = 0;	
	for (size_t i = 0; i < A.size(); i++)
		sum = sum + A[i];

	return sum;
}

void printIntVector(const vector<int>& A)
{
	cout << "Elem #" << "  Value\n";
	cout << "~~~~~~" << "  ~~~~~~~~\n";

	for (size_t i = 0; i < A.size(); ++i)
		cout << setw(6) << right << i << "  " << left << A[i] << endl;
}

// The function definitions for C-Array
void randomInt_C_Array(int* A, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		A[i] = 1 + (rand() + i) % (size * 10); // this reduces duplicates.
}

int sumOfInt_C_Array(const int* A, size_t size)
{
	int sum = 0;
	for (size_t i = 0; i < size; i++)
		sum = sum + A[i];

	return sum;
}

void printInt_C_Array(const int* A, size_t size)
{
	cout << "Elem #" << "  Value\n";
	cout << "~~~~~~" << "  ~~~~~~~~\n";
	
	for (size_t i = 0; i < size; ++i)
		cout << setw(6) << right << i << "  " << left << A[i] << endl;
}

/*
==============================================================
Please defines the following functions declared before main().
<<<<<< Your code below... >>>>>
==============================================================
*/
void findMinMaxIntVector(const vector<int>& A, int& max, int& max_i, int& min, int& min_i)
{
	max = min = A[0];
	max_i = min_i = 0;
	
	for(size_t i = 1; i < A.size(); ++i)
	{
	    if (A[i] > max)
	    {
	        max = A[i];
	        max_i = i;
	    }
	    
	}
		for(size_t i = 1; i < A.size(); ++i)
	{
	    if (A[i] < min)
	    {
	        min = A[i];
	        min_i = i;
	    }
	}
}

// Uncomment and define the following function.

double averageInt_C_Array(const int* A, size_t size)
{
	int sum = 0;
	double avg = 0;
	for (size_t i = 0; i < size; i++)
		sum = sum + A[i];
		avg = static_cast<double>(sum) / (size - 1);

	return avg;
    
}


/* A Sample Output
================================================================
Harper CSC122-S01 by Mr. Jin Guo: Assignment #4, Spring 2021
Student: <Your Name>

This program will fill in data for a C-array or a C++ vector,
find the sum, maximum and minimum elements and average.
================================================================

>>> Generate some random numbers for vector A ...
Elem #  Value
~~~~~~  ~~~~~~~~
     0  48
     1  88
     2  15
     3  44
     4  74
     5  56
     6  71
     7  39
     8  64

>>> Find the sum of all elements in this vector ...
The sum is: 499

>>> Find the maximum and minimum values in this vector...
The maximum value is: A[1] = 88
The minimum value is: A[2] = 15

============================================
The following code is for integer array...
============================================

>>> Fill in some randdom numbers for array B ...
Elem #  Value
~~~~~~  ~~~~~~~~
     0  64
     1  19
     2  12
     3  24
     4  52
     5  8
     6  23
     7  13
     8  65

>>> Find the sum of all elements in this vector ...
The sum is: 280

>>> Find the average of B ...
The average: 31.11

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


