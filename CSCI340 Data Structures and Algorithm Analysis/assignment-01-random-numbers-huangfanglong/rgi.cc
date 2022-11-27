/*
	Long Fang Huang (Z1942308)
	Assignment 01
	09/02/2021
	
	I certify that this is my own work and where appropriate an
	extension of the starter code provided for the assignment.
*/

#include "rgi.h"

// Add needed constants
using std::vector;  //automatically apply namespace std in front of vector
using std::cout;	//same but for cout

int LOW = 1;
int HIGH = 10000;

// Add code for genRndNums
void genRndNums(vector<int> &v, int num)
{
	srand(1);		//random number generator with SEED = 1
	for (int i = 0; i <= 200; i++)		//insert 200 random numbers to v
	{
		num = rand() % (HIGH - LOW) + LOW;
		v.push_back(num);
	}
}
// Add code for printVec
void printVec(const vector<int> &v)
{
	const int NO_ITEMS = 12;
	
		for(int i = 0; i < v.size(); i++)
		{
			std::cout << std::right << std::setw(5) << v.at(i);
			if (i % NO_ITEMS == (NO_ITEMS - 1)){ std::cout << std::endl; }		//new row when there are 12 numbers on a line
		}
}

int 
main() 
{
// Declare vector v
vector<int> v;

// Generate random numbers to fill vector v	
genRndNums(v, 1);

// Using STL sort sort v
std::sort(v.begin(), v.end());
	
// Print vector of sorted random numbers
printVec(v);

    return 1;
}


