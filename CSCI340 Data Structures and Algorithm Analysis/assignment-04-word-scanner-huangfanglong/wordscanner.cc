/*
 * Long F. Huang (Z1942308)
 * Assignment 04
 * 09/30/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/

#include <iostream>
#include <map>
#include <algorithm>	//for for_each
#include <fstream>		//for reading from input stream
#include <string>		//for substr
#include <iomanip>		//for setw

//Gets a word from the input stream and removes its punctuation marks
void get_words(std::map<std::string, int>&, std::ifstream& infile);

//Prints the final list of words and their frequencies, it also prints 
//the number of nonempty words and the number of distinct words in the 
//input stream
void print_words(const std::map<std::string, int>&);

//Cleans a word from its punctuation marks, the first argument is the
//original word in the input stream and the second argument contains the
//same word after cleaning
void clean_entry(const std::string&, std::string&);

//Convert uppercase chars to lowercase, using as an unary argument
//for for_each
void lowerUppercase(char& c) 
{
   c = tolower(c);
   return;
}

//definining cout(display) procedures
#define NO_ITEMS 4
#define ITEM_WORD_WIDTH 14
#define ITEM_COUNT_WIDTH 3

std::map<std::string, int> words;	//word map container

//Calls the subroutine get_words() to get words from the input stream. 
//To clean an individual word from its punctuation marks, get_words() 
//calls the subroutine clean_entry()

int main()
{
	//read the file
	std::ifstream is("wordscanner.in");
	
	get_words(words, is);
	
	print_words(words);

	return 0;
}

void get_words(std::map<std::string, int>& m, std::ifstream& infile)
{
	std::string s, w;
	
	while (!infile.eof())
	{
		//clean each word as it gets scanned
		while(infile >> s)
		{
			clean_entry(s, w);
			
			//if the size of a string scanned is bigger than 0, input it
			//into map container and updates
			if (w.length() > 0)
			{
				m[w]++;
			}
		}
	}
	return;
}


void print_words(const std::map<std::string, int>& m)
{	
	//initialize counter for row and line of columns
	int elem = 0, line = 0;
	
	//loop using iterator it to print out map contents
	for (auto it : m)
	{
		
		std::cout << std::setw(ITEM_WORD_WIDTH) << std::left << it.first
					<< " :" << std::setw(ITEM_COUNT_WIDTH) << it.second;
					
		elem++;
		line += it.second;
		
		//start new line once row reached the defined number
		if (elem == NO_ITEMS)
		{
			//reset counter for new row
			elem = 0;
			std::cout << std::endl;
		}
	}
	
	std::cout << std::endl << std::endl;
	
	std::cout << "no of words in input stream: " << line << std::endl;
	std::cout << "no of words in output stream: " << m.size() << std::endl;

}

void clean_entry(const std::string& s, std::string& w)
{
	//initial pos of word and length of word
   int pos = 0,len = 0;
   
   //flag to recognize when the start and end of each word is reached.
   //flag to recognize punctuations 
   bool start = false, end = false, Punc = false;
   for (int i = 0; i < (int)s.length(); i++)
   {
	   //if not an alpha/numeric char, is punctuation
       if (isalnum(s[i]) == false)
       {
           Punc = true;
       }
       
       //if is alpha/numeric char and is not a new word,
       //start scanning new word; setting initial pos to position.
       if (isalnum(s[i]) == true && start == false)
       {
           start = true;
           pos = i;
       }
       
       //if currently a word and if position is not alpha/numeric, end
       //the word and mark it.
       if (start == true) {
           if (isalnum(s[i]) == false) {
               end = true;
               len = i;
           }
       }
       
       if (end == true) {
           break;
       }
   }
   
   //Copy the word from the first alphanumeric character until the last 
   //one to another string.
   w = s.substr(pos, len);
   
   //convert capital letters in the cleaned word to lowercase letters
   for_each(w.begin(), w.end(), lowerUppercase);
   
   //if the word does not contain or is not a punctuation, set them
   //equal and convert capital letts to lowercase;
   if (Punc == false)
   {
       w = s;
       for_each(w.begin(), w.end(), lowerUppercase);
   }
}
