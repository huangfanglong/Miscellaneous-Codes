/*
 * Long F. Huang (Z1942308)
 * Assignment 02
 * 09/17/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/

#include "matrix.h"

using namespace std;

void open_files(ifstream &is1, ifstream &is2)
{
	is1.open(FILE1);
	if (is1.fail())
	{
		cerr << "Error opening " << FILE1 << "\n";
		
		abort();
	}
	
	is2.open(FILE2);
	if (is2.fail())
	{
		cerr << "Error opening " << FILE2 << "\n";
		
		abort();
	}
}

void read_data(ifstream &is, vector<vector<int>> &m)
{	
	for(int i = 0; i < m.size(); i++)
	{
		for(int j = 0; j < m[i].size(); j++)
		{
			is >> m[i][j];
		}
	}
}

void gen_data(const vector<vector<int>> &A, 
				const vector<vector<int>> &B, 
					vector<vector<int>> &C)
{
	for (i = 0; i < A.size(); i++)
	{
		for (j = 0; j < B[0].size(); j++)
		{
			for (k = 0; k < A[0].size(); k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void print_data(const vector<vector<int>> &m)
{
	cout << m.size() << " x " << m[0].size() << endl;
	for (i = 0; i < m.size(); i++)
	{
		for(j = 0; j < m[i].size(); j++)
		{
			cout << setw(ITEM_W) << m[i][j] << " ";
		}
		cout << endl;
	}
}
