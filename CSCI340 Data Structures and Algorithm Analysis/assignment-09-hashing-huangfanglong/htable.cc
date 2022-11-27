/*
 * Long F. Huang (Z1942308)
 * Assignment 09
 * 11/13/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/
#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...

//Constructor
//The hash table, which is a vector of list containers, can be created 
//dynamically for a given fixed size hs by its constructor. Initially, 
//the pointer table, which is a vector of type Entry *, is empty but its
//size will increase dynamically after inserting a new Entry item in this
//table, which is the address of the inserted item in the corresponding list container.
HT::HT(const unsigned &hs) 
{
	hsize = hs;
	hTable.resize(hs);
	pTable.resize(0);
}

//Destructor of the hash table first frees the memory for all list containers 
//and then frees the memory for the vector containers for the hash table and the pointer table.
HT::~HT() 
{
	hTable.clear();
	pTable.clear();
}


//This public function inserts the record of the item e:(key, desc, num) 
//in the hash table. If the key already exists in the table, then the function prints an error message;
//otherwise, it prints the index value of the inserted record in the hash table and it also inserts 
//the address of the record (in the hash table) into the pointer table.
void HT::insert(const Entry &e) 
{
	int index = hash(e.key);
	auto& cell = hTable[index];
	auto bItr = begin(cell);
	bool keyExists = false;
	for(; bItr != end(cell); bItr++)
	{
		if(bItr->key == e.key)
		{
			keyExists = true;
			std::cout << " not inserted - duplicate key!!!" << std::endl;
			break;
		}
	}
	
	if(keyExists == false)
	{
		//inserting entry into first slot in the case of a collision using separate chaining
		hTable[index].push_front(e);
		//inserting that slot from hashtable into pointer table so that pointer table point to the same address
		pTable.push_back(&hTable[index].front());
		std::cout << " entry = " << index << std::endl;
	}
	return;
}

//Searches the hash table for a record with key
void HT::search(const string &s) 
{
	int index = hash(s);
	auto& cell = hTable[index];
	auto bItr = begin(cell);
	bool keyExists = false;
	for(; bItr != end(cell); bItr++)
	{
		if(bItr->key == s)
		{
			keyExists = true;
			std::cout << " ==> number: " << std::setw(4) << bItr->num << " - item:" << bItr->desc << std::endl;
			break;
		}
	}
	
	//if bool keyExists did not change to true in for loop, return false in search
	if(!keyExists)
	{
		std::cout << "key " << s << " not in table!!" << std::endl;
	}	
}

//printing hash table
void HT::hTable_print() 
{
	std::cout << std::endl;
	for(int i = 0; (long unsigned int)i < hTable.size(); i++)
	{
		if(hTable[i].size() == 0)
		{
			continue;
		}
		else
		{
			auto bItr = hTable[i].begin();
			for(; bItr != hTable[i].end(); bItr++)
			{
				std::cout << std::setw(4) << hash(bItr->key) << ":  " << bItr->key << "  - " << std::setw(5) << bItr->num << "     " << std::setw(6) << bItr->desc << std::endl;
			}
		}
	}
	return;
}

//bool function to use cmp to sort alphabetically
bool alphabetSort(Entry* a, Entry* b)
{if (a->key < b->key) return true; return false;}

//printing pointer table
void HT::pTable_print() 
{
	std::sort(pTable.begin(), pTable.end(), alphabetSort);
    for (unsigned int i = 0; i < pTable.size(); i++) 
    {
		std::cout << " " << std::setw(5) << pTable[i]->key << "  -" << std::setw(6) << pTable[i]->num << "  -  " << pTable[i]->desc << std::endl;
    }
	return;
}
