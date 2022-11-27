/*
 * Long F. Huang (Z1942308)
 * Assignment 06
 * 10/16/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/

#include "josephus.h"
#include <fstream>

int main()
{
	list<string> names;
	//initialize count for total num of removed
	int cnt = 0;
	//initialize object for struct args
	struct args input;
	//read file for input and assign each value accordingly to N M and K
	//of struct args object 'input'
	ifstream file("josephus.d");
	file >> input.N >> input.M >> input.K;
	
	init_vals(names, input);
	print_list(names, cnt);

	//initialize variable j for the position of the M^th person from the position i
	//and variable i to represent a position of a person in list names
	auto j = 0;
	int i = 0;
	
	//until there is only 1 left, continue removing according to pattern
	while(names.size() > 1)
	{
			//return j as position of M^th person to be removed
			j = (i + (input.M - 1))%names.size();
			//set i = j to reset to new position to begin pattern again
			i = j;
			//convert the index value j to an iterator by the advance(p, j) function
			//and use the erase function to remove it then increment cnt(num of removed)
			list<string>::iterator p = names.begin();
			advance(p, j);
			names.erase(p);
			cnt++;
		
		//if there's not enough left or if there is only one left, print for last time and stop
		if (cnt % input.K == 0 || names.size()== 1)
		{
			print_list(names,cnt);
		}
	}
	
return 0;
}
