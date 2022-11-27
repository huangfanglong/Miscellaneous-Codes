/*
 * Long F. Huang (Z1942308)
 * Assignment 03
 * 09/20/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/

#include <iostream>
#include <set>
#include <iterator> //for itr using with set
#include <iomanip> //for setw

#define ITEM_W 5      // for spacing
#define NO_ITEMS 16   //for 16 elem per row

using std::set;

void sieve(set<int>& s, int n);

void print_primes(const set<int>& s);

int
main()
{
	set<int> integers;
	int n;
	
	//prompting for user input
	std::cout << "Upper limit for the set of primes: ";
	std::cin >> n;
	std::cout << std::endl;
	
	//printing a message to let user know that the number entered is
	//invalid and abort the program
	if (n < 2)
	{ 
		std::cerr << "Upper limit for the set of primes is less than 2!";
		abort();
	}
	
	sieve(integers, n);
	
	print_primes(integers);
	
	return 0;
}

void sieve(set<int> &s, int n)
{
	//inserting all elem from 2 to n
	for(int i = 2; i >= 2 && i <= n; i++)
	{
		s.insert(i);
	}
	
	//removing multiples from the inserted elements in the set
	for(std::set<int>::iterator it=s.begin(); it!=s.end() && *it < n; ++it)
	{
		for(int j = 2; j * *it <= n; j++)
		{
			s.erase(j * *it);
		}
	}
	
}

void print_primes(const set<int> &s)
{
	
	set<int>::iterator itr; //setting up iterator for ease of use
    for (itr = s.begin(); itr != s.end(); itr++)
    {
        std::cout << std::setw(ITEM_W) << *itr ; //setting spacing
        
        if(*itr % NO_ITEMS == 0) //setting max num of results per row
        {
			std::cout << std::endl;
		}
    }
}
