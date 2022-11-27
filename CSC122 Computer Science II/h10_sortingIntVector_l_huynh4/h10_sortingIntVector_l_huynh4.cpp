/*
==========================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Algorithm Analysis
Program Description:
	This program implements some sorting algorithms for an int vector. User is
	prompted to	input the size of a vector. User is then prompted to decide the
	vector is either random or in order. The program will generate an int vector
	of the given size and then sort the vector. The time is measured for each
	sorting algorithm so user can compare the efficiency of different algorithms
	with different data sizes and different data patterns (ordered or not).

Instructions:
	1. Understand and run the given program. Don't remove any code, just add yours.
		Add your code wherever is marked "Your code below... ".
	2. Try to understand the program as much as you can. You are required to add
		Select-sort (refer to s13a) and Bubble-sort (write your own or
		search on Internet) in the given context. There are many versions of
		Bubble-sort. Yours should be able to stop sorting when the vector is
		already in order. You may add more sort algorithms if you want to.
	3. Please follow the code style and conventions in the program.
	4. Run the executable h10_JG.out and your finished program should perform the
		same as this one does.
	5. Please name your file properly as usual.

Notes:
	1. size_t is a type "unsigned int". It's usually used for size and position.
	2. swap() is defined in standard library <algorithm>.
	3. On Bb: CSC121 CS Videos -> Sorting Algorithms -> Bubble-sort with Hungarian dance

Created:	3/9/2010 by Jin Guo
Updated:	4/20/2015 by Jin Guo. Customized for Harper.
Updated:	4/17/2016 by Jin Guo. Added merge-sort for this semester.
Updated:	4/21/2021 by Jin Guo. Simplified and removed some functions.
==========================================================================================
*/
#include <iostream>
#include <vector>
#include <string>		// to_string()
#include <iomanip>		// for setw(), setprecision()
#include <cstdlib>		// for srand(), rand()
#include <ctime>		// for CLOCKS_PER_SEC, difftime() and time() 
#include <algorithm>	// for swap(), random_shuffle() and sort()

using namespace std;

// Define the function type for sorting algorithm
typedef void(*SortAlgorithmX)(vector<int>& A);

// Generates ordered integers for an int vector
void fillInVector(vector<int>& A);

// Measure the time for a passed-in sorting algorithm
void sortAlgorithmX_timeSpent(SortAlgorithmX sortAlgorithmX, vector<int>& A);

// Run all implemented sorting algorithms
void sortManyAlgorithms(const vector<int>& A);

// Print out the vector
void printIntVector(const vector<int>& A);

// Copy vector A into vector R, same as R = A or R.assign(A.begin(), A.end()).
void copyIntVector(const vector<int>& A, vector<int>& R);

/*
======================================
Sorting algorithms
======================================
*/

/*
The sorting algorithm from C++ library <algorithm>.
Notes: It uses quick sorting as qsort in C, but written in class template.
*/
void sortCplusplusLibSort(vector<int>& A);

// Insert-sorting
void sortInsertion(vector<int>& A);

// Merge-sorting
void merge2HalfsOfVector(vector<int>& A, size_t from, size_t mid, size_t to);
void mergeSort(vector<int>& A, size_t from, size_t to);
void sortMerge(vector<int>& A) { mergeSort(A, 0, A.size() - 1); }

/*
==========================================================
You need to define these functions after main().
<<<<<< Your code below ... >>>>>
==========================================================
*/
// The Bubble-sorting
void sortBubble(vector<int>& A);

// The Selection-sorting
void sortSelection(vector<int>& A);

int main()
{
	cout << "===================================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #10, Spring 2021\n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program sorts a vector with different sorting algorithms.\n";
	cout << "====================================================================\n";

	string choice;
	do
	{
		int SIZE;

		cout << "\n>>> Let us play with sorting algorithms ...>>>\n\n";
		cout << "==> Please input the size of an integer vector: ";
		cin >> SIZE;
		cin.ignore(256, '\n');

		vector<int> A(SIZE);	// construct vector A for the input size
		fillInVector(A);		// fill A with values in order.

		char c;
		cout << "==> Do you want the vector in random order? (y/n): ";
		cin >> c;
		cin.ignore(256, '\n');

		if (c == 'y')			// shuffle A so data is in random.
			random_shuffle(A.begin(), A.end());

		sortManyAlgorithms(A);

		cout << "\n=================================================================\n";
		cout << "==> Do you want to play this again? y(es) or n(o): ";
		cin >> ws; // skip white space of input
		getline(cin, choice);

	} while (!(choice.find("no") != -1 || choice[0] == 'n'));

	cout << "\n=== Thanks for using! See you next time! ===\n\n";
}

/*
============================================
Definitions of functions
============================================
*/
void fillInVector(vector<int>& A)
{
	for (size_t i = 0; i < A.size(); ++i)
		A[i] = i + 1;
}

void sortAlgorithmX_timeSpent(SortAlgorithmX sortAlgorithmX, vector<int>& A)
{
	time_t time_start, time_end;     // record wall clock time elapsed.
	clock_t clock_begin, clock_stop; // record CPU time used by the operation.

	time(&time_start);
	clock_begin = clock();

	sortAlgorithmX(A);

	clock_stop = clock();
	time(&time_end);

	double user_time = (int64_t)(clock_stop - clock_begin) / (double)CLOCKS_PER_SEC;
	double wall_time = difftime(time_end, time_start);

	cout << fixed << setprecision(4);
	cout << "--------------------------------------\n";
	cout << "| CPU time used :     " << user_time << " seconds.|\n";
	cout << "| Wall clock passed : " << wall_time << " seconds.|\n";
	cout << "--------------------------------------\n";
}

void sortManyAlgorithms(const vector<int>& A)
{
	vector<int> R;

	cout << "\nThe original vector A: \n";
	printIntVector(A);

	cout << "\nCopy vector A into vector R ...\n";
	copyIntVector(A, R);
	cout << ">>>> Use <<< Quick-sort >>> algorithm from library <algorithm> ...\n";
	sortAlgorithmX_timeSpent(sortCplusplusLibSort, R); // sorting R in place.
	cout << "\nAfter sorting with sortCplusplusLibSort, the reult R: \n";
	printIntVector(R);

	cout << "\nCopy vector A into vector R ...\n";
	copyIntVector(A, R);
	cout << ">>>>> Use <<< Merge-sort >>> algorithm ...\n";
	sortAlgorithmX_timeSpent(sortMerge, R); // sorting R in place.
	cout << "\nAfter sorting with sortMerge, the reult R: \n";
	printIntVector(R);

	cout << "\nCopy vector A into vector R ...\n";
	copyIntVector(A, R);
	cout << ">>>> Use <<< Insert-sort >>> algorithm ...\n";
	sortAlgorithmX_timeSpent(sortInsertion, R); // sorting R in place.
	cout << "\nAfter sorting with sortInsertion, the reult R: \n";
	printIntVector(R);

	cout << "\n===========================================================";
	cout << "\n<<<<<<<<< I added the following sort algorithms >>>>>>>>>";
	cout << "\n===========================================================\n";
	/*
	==========================================================
	<<<<<< Your code below... >>>>>
	==========================================================
	*/
	cout << "\nCopy vector A into vector R ...\n";
	copyIntVector(A, R);
	cout << ">>>> Use <<< Bubble-sort >>> algorithm ...\n";
	sortAlgorithmX_timeSpent(sortBubble, R);
	cout << "\nAfter sorting with sortBubble, the result R: \n";
	printIntVector(R);

	cout << "\nCopy vector A into vector R ...\n";
	copyIntVector(A, R);
	cout << ">>>> Use <<< Selection-sort >>> algorithm ...\n";
	sortAlgorithmX_timeSpent(sortSelection, R);
	cout << "\nAfter sorting with sortSelection, the reuslt R: \n";
	printIntVector(R);
}

void printIntVector(const vector<int>& A)
{
	size_t size = A.size();

	const size_t PRINTED_SIZE = 20;
	const int NUM_WIDTH = to_string(size - 1).size() + 2;
	const int ITEMS_PER_LINE = 10;

	size_t tmp_size = (size <= PRINTED_SIZE) ? size : PRINTED_SIZE;

	if (size > PRINTED_SIZE && size <= 2 * PRINTED_SIZE)
	{
		cout << "(The vector of " << size << " is a little large, \n";
		cout << "only first " << PRINTED_SIZE << " elements are printed out!)\n";
	}
	else if (size > 2 * PRINTED_SIZE)
	{
		cout << "(The vector of " << size << " is too large, \n"
			<< "only first and last " << PRINTED_SIZE << " elements are printed out!)\n";
	}

	cout << "-----------------------------------------------------------------\n";

	for (size_t i = 0; i < tmp_size; i++)
	{
		if (i != 0 && i % ITEMS_PER_LINE == 0)
			cout << "\n";

		cout << setw(NUM_WIDTH) << left << fixed << A[i];
	}

	if (size <= PRINTED_SIZE)
	{
		cout << "\n-----------------------------------------------------------------\n";
		return;
	}

	cout << "\n.................................................................\n";

	if (size > 2 * PRINTED_SIZE)
	{
		for (size_t i = size - PRINTED_SIZE, k = 0; i < size; i++, k++)
		{
			if (k != 0 && k % ITEMS_PER_LINE == 0)
				cout << "\n";

			cout << setw(NUM_WIDTH) << left << fixed << A[i];
		}
	}

	cout << "\n-----------------------------------------------------------------\n";
}

void copyIntVector(const vector<int>& A, vector<int>& R)
{
	size_t size = A.size();

	if (size != R.size())
		R.resize(size);

	for (size_t i = 0; i < size; i++)
		R[i] = A[i];
}

/*
============================================
Sorting algorithms
============================================
*/
void sortCplusplusLibSort(vector<int>& A)
{
	sort(A.begin(), A.end());
}

void sortInsertion(vector<int>& A)
{
	size_t size = A.size();
	size_t j, k;
	int temp;

	for (k = 1; k < size; k++)
	{
		temp = A[k];
		j = k;

		while (j > 0 && A[j - 1] > temp)
		{
			A[j] = A[j - 1];
			j--;
		}
		if (j != k)
			A[j] = temp;
	}
}

void merge2HalfsOfVector(vector<int>& A, size_t from, size_t mid, size_t to)
{
	size_t n = to - from + 1;	// size of the range to be merged.
	vector<int> B(n);		// merge both halves into a vector B.

	size_t i1 = from;			// start index in the first half. 
	size_t i2 = mid + 1;		// start index in the second half. 
	size_t j = 0;				// current position in B. 

	/**
	Compare A[i1] and A[i2] until either of i1 and i2 reaches the end,
	move the smaller one into B.
	*/
	while (i1 <= mid && i2 <= to)
	{
		if (A[i1] < A[i2])
			B[j++] = A[i1++];
		else
			B[j++] = A[i2++];
	}

	while (i1 <= mid)	// copy any remaining entries of the first half.
		B[j++] = A[i1++];

	while (i2 <= to)	// copy any remaining entries of the second half.
		B[j++] = A[i2++];

	for (j = 0; j < n; j++) // copy back from the temporary vector.
		A[from + j] = B[j];
}

void mergeSort(vector<int>& A, size_t from, size_t to)
{
	if (from == to)
		return;

	size_t mid = (from + to) / 2;

	mergeSort(A, from, mid);
	mergeSort(A, mid + 1, to);
	merge2HalfsOfVector(A, from, mid, to);
}

/*
==========================================================
<<<<<< Your code below... >>>>>
==========================================================
*/
// The Bubble-sorting
void sortBubble(vector<int>& A)
{
	bool swapp = true;
	while (swapp)
	{
		swapp = false;
		for (size_t i = 0; i < A.size() - 1; i++)
		{
			if (A[i] > A[i + 1])
			{
				A[i] += A[i + 1];
				A[i + 1] = A[i] - A[i + 1];
				A[i] -= A[i + 1];
				swapp = true;
			}
		}
	}
}

// The Selection-sorting
void sortSelection(vector<int>& A)
{
	size_t size = A.size();
	size_t i, j, min_i;

	for (i = 0; i < size - 1; i++)
	{
		min_i = i;
		for (j = i + 1; j < size; j++)
		{
			if (A[min_i] > A[j])
				min_i = j;
		}

		if (min_i != i)
			swap(A[min_i], A[i]);
	}
}

