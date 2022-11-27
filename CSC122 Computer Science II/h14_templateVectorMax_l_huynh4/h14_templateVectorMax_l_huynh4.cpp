/*
=======================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Function Template maxOfVector()
Program Description:
	This program demonstrates how a function template is defined and used. The same
	function name can be both overloaded and has its function template. When a 
	function template is called, a function instance (specialization) can be invoked
	implicitly or explicitly. This program implements both function overloading and
	function template on maxOfVector(), which is used to find the maximum of a vector.

	When a function is both overloaded and has its template, compiler first
	check the overloaded versions to find a match.

Instructions:
	1. Run and understand the given program. Don't remove any code, just add yours.
		Add your code wherever is marked "Your code below ... ".
	2. maxOfVector() is overloaded. You are required to write a function 
		template of this overloaded function. 
	3. Add your code in main() to test your definition of maxOfVector() template.
	4. Run the executable h14_JG.out and your finished program should perform the 
		same as this one does. 
	5. Please name your file properly as usual.

Created: 5/3/2021 by Jin Guo
=======================================================================================
*/
#include <iostream>	
#include <vector>
#include <string>

using namespace std;

// Find maximum element of vector<int> A.
void maxOfVector(const vector<int>& A, int& max, size_t& max_i);

// Find maximum element of vector<double> A.
void maxOfVector(const vector<double>& A, double& max, size_t& max_i);

/*
=========================================================================
Declare function template maxOfVector() below and define it after main().
<<<<<< Your code below ... >>>>>
=========================================================================
*/
// Find maximum element of any fundamental vector.
template <typename T>
void maxOfVector(const vector<T>& A, T& max, size_t& max_i);

int main()
{
	cout << "=========================================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #14, Spring 2021 \n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program overloads function maxOfVector() and also defines a\n";
	cout << "function template for it.\n";
	cout << "=========================================================================\n\n";

	vector<int> intV { 11, 22, 99, 33, 44, 55, 88, 66, 77 };
	vector<double> doubleV { 1.1, 2.2, 3.3, 9.9, 4.4, 8.8, 5.5, 6.6, 7.7 };
	vector<char> charV { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'k', 'i', 'j' };
	vector<string> stringV{ "Four", "score", "and", "seven", "years", "ago" };

	cout << "intV =    { 11, 22, 99, 33, 44, 55, 88, 66, 77 }\n";
	cout << "doubleV = { 1.1, 2.2, 3.3, 9.9, 4.4, 8.8, 5.5, 6.6, 7.7 }\n";
	cout << "charV =   { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'k', 'i', 'j' }\n";
	cout << "stringV = { \"Four\", \"score\", \"and\", \"seven\", \"years\", \"ago\" }\n";

	int max_int;
	double max_double;
	char max_char;
	string max_string;
	size_t max_i;

	cout << "\n>>> Call maxOfVector(intV, max_int, max_i) ...\n";
	cout << "Invoke overloaded maxOfVector(const vector<int>&, int&, size_t&) ...\n";
	maxOfVector(intV, max_int, max_i);	
	cout << "==> The maximum is: intV[" << max_i << "] = " << max_int << endl;

	cout << "\n>>> Call maxOfVector(doubleV, max_double, max_i) ...\n";
	cout << "Invoke overloaded maxOfVector(const vector<double>&, double&, size_t&) ...\n";
	maxOfVector(doubleV, max_double, max_i);
	cout << "==> The maximum is: doubleV[" << max_i << "] = " << max_double << endl;

	cout << "\n";
	cout << "=============================================\n";
	cout << "<<<<<<< My testing code below ... >>>>>>>>\n";
	cout << "=============================================\n";
	/*
	===================================================================
	After you defined function template printVector(),
	uncomment lines below of invoking the function template explicitly.
	<<<<<< Your code below ... >>>>>
	===================================================================
	*/	
	cout << ">>> Call maxOfVector<char>(charV, max_char, max_i) ...\n";
	cout << "Invoke template maxOfVector(const vector<T>&, T&, size_t&) explicitly ...\n";
	maxOfVector<char>(charV, max_char, max_i);
	cout << "==> The maximum is: charV[" << max_i << "] = " << max_char << endl;

	cout << ">>> Call maxOfVector(stringV, max_string, max_i) ...\n";
	cout << "Invoke template maxOfVector(const vector<T>&, T&, size_t&) implicitly ...\n";
	maxOfVector(stringV, max_string, max_i);
	cout << "==> The maximum is: stringV[" << max_i << "] = " << max_string << endl;

	cout << endl;
}

//==============================================================================
void maxOfVector(const vector<int>& A, int& max, size_t& max_i)
{
	max = A[0];
	max_i = 0;

	for (size_t i = 1; i < A.size(); ++i)
	{
		if (A[i] > max)
		{
			max = A[i];
			max_i = i;
		}
	}
}

void maxOfVector(const vector<double>& A, double& max, size_t& max_i)
{
	max = A[0];
	max_i = 0;

	for (size_t i = 1; i < A.size(); ++i)
	{
		if (A[i] > max)
		{
			max = A[i];
			max_i = i;
		}
	}
}

/*
===================================================================
Define the function template maxOfVector declared before main().
<<<<<< Your code below ... >>>>>
===================================================================
*/
template <typename T>
void maxOfVector(const vector<T>& A, T& max, size_t& max_i)
{
	max = A[0];
	max_i = 0;

	for (size_t i = 1; i < A.size(); ++i)
	{
		if (A[i] > max)
		{
			max = A[i];
			max_i = i;
		}
	}
}

/* A Sample Output
=========================================================================
Harper CSC122-S01 by Mr. Jin Guo: Assignment #14, Spring 2021
Student: <Your Name>

This program overloads function maxOfVector() and also defines a
function template for it.
=========================================================================

intV =    { 11, 22, 99, 33, 44, 55, 88, 66, 77 }
doubleV = { 1.1, 2.2, 3.3, 9.9, 4.4, 8.8, 5.5, 6.6, 7.7 }
charV =   { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'k', 'i', 'j' }
stringV = { "Four", "score", "and", "seven", "years", "ago" }

>>> Call maxOfVector(intV, max_int, max_i) ...
Invoke overloaded maxOfVector(const vector<int>&, int&, size_t&) ...
==> The maximum is: intV[2] = 99

>>> Call maxOfVector(doubleV, max_double, max_i) ...
Invoke overloaded maxOfVector(const vector<double>&, double&, size_t&) ...
==> The maximum is: doubleV[3] = 9.9

=============================================
<<<<<<< My testing code below ... >>>>>>>>
=============================================

>>> Call maxOfVector<char>(charV, max_char, max_i) ...
Invoke template maxOfVector(const vector<T>&, T&, size_t&) explicitly ...
==> The maximum is: charV[7] = k

>>> Call maxOfVector(stringV, max_string, max_i) ...
Invoke template maxOfVector(const vector<T>&, T&, size_t&) implicitly ...
==> The maximum is: stringV[4] = years

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

