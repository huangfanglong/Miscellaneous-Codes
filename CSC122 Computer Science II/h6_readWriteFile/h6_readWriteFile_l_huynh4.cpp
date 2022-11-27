/*
====================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: Long Huynh

Program Name: Reading from and writing to file
Program Description:
	Many applications need to read data from file, and process the data and then 
	write them back to file. This program is a demo of how to read from and write 
	to file. It will read a name list from a file, sort the list and then write the 
	sorted list to another file.

Instructions:
	1. Run h6_JG.out on Unix/Ares. It is the finished executable. Your finished 
		program should perform the same as this one does. Imitate its prompts 
		and output.
	2. You need to define the declared function writeNamesToFile(..). The name list
		should be sorted in main() before it's written to file.
	3. When you are done with the above, test your code in the main().
	4. Add your code to wherever marked as "Your code below...". Please do
		not remove any existing statements.
	5. Submit ONLY your h6_readWriteFile_yrlogin.cpp file as usual.

Input Files: h6_10names_in.txt
Output File: h6_10names_out.txt

Notes: 
	1. For sorting, you are required to use the library function sort().
	2. Refer to Textbook Chapter 14: File Processing.
	3. If you use Visual Studio, you need to change the working dir as follows:
		1) Go to the project name, right click on it and choose "Properties".
		2) Click on "Debugging", on the "Working Directory", type 
			the directory which contains the input file, e.g.,
			$(ProjectDir)h6_read_write_file
		3) Or, instead of doing the above 1) and 2), you may copy h6_10names_in.txt
			under your project dir. Then your output file will be also be under 
			your project dir.

Created: 10/23/2017 by Jin Guo.
Updated: 3/5/2021 by Jin Guo. Adapted for this semester.
=====================================================================================
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>		// for ifstream/ofstream
#include <sstream>		// for istringstream 
#include <algorithm>	// for sort()

using namespace std;

/**
For the name list in vector<string> "names", put last name first,
then comma, then first name.
*/
void lastNameFirstPlusComma(vector<string>& names);

// Print the name list in vector<string> "names" on screen.
void printStringVector(const vector<string>& names);

// Read the name list into vector<string> "names" from file "in".
void readNamesFromFile(vector<string>& names, ifstream& in);

/*
================================================================
Your are required to define the following function after main().
<<<<<< Your code below... >>>>>
================================================================
*/
// Write the name list in vector<string> "names" to file "out"
void writeNamesToFile(const vector<string> &names, ofstream& out);

int main()
{
	cout << "=================================================================\n";
	cout << "Harper CSC122-S01 by Mr. Jin Guo: Assignment #6, Spring 2021 \n";
	cout << "Student: Long Huynh\n\n";
	cout << "This program will read a name list from a file, sort the list and\n";
	cout << "then write the sorted list to another file.\n";
	cout << "=================================================================\n\n";

	string inFile, outFile; // for input/output file name.
	ifstream inF;			// for input file stream.
	ofstream outF;			// for output file stream.

	cout << "Please enter the file name of the name list ==> ";
	cin >> inFile;
	inF.open(inFile.c_str());
	if (inF.fail())
	{
		cout << "Error opening " << inFile << "!\n";
		return 1;
	}

	vector<string> nameList;
	readNamesFromFile(nameList, inF);
	inF.close();

	cout << "\n>>> This is the original name list in the file:\n";
	cout << "___________________________\n";
	printStringVector(nameList);

	cout << "\n>>> Put the last name first ...\n";
	lastNameFirstPlusComma(nameList);
	cout << "___________________________\n";
	printStringVector(nameList);

	/*
	=======================================================================
	Your are required to sort the above the nameList and then write it
	to a file, whose name should be input from keyboard.
	<<<<<< Your code below... >>>>>
	========================================================================
	*/
	cout << ">>> Sorting the name list ..." << endl;

	cout << "___________________________" << endl;

	sort(nameList.begin(), nameList.end());

	printStringVector(nameList);

	cout << "Please name the file for the sorted name list ==> ";

	cin >> outFile;

	outF.open(outFile.c_str());

	if (outF.fail())
	{
		cout << "Error opening or creating " << outFile << "!\n";
		return 1;
	}

	writeNamesToFile(nameList, outF);

	outF.close();
	
	cout << "Done. Please check the sorted name list in the file " << outFile << endl;

	return 0;
}

//===========================================

void writeNamesToFile(const vector<string>& A, ofstream& out)
{
	for (size_t i = 0; i < A.size(); i++)
		out << A[i] << endl;
}


void lastNameFirstPlusComma(vector<string>& A)
{
	string s1, s2;

	for (size_t i = 0; i < A.size(); i++)
	{
		istringstream input(A[i]);
		input >> s1 >> s2;
		A[i] = s2 + ", " + s1;
	}
}

void readNamesFromFile(vector<string>& names, ifstream& in)
{
	string name;

	getline(in, name);
	while (!in.fail())
	{
		names.push_back(name);
		getline(in, name);
	};
}

void printStringVector(const vector<string>& A)
{
	for (size_t i = 0; i < A.size(); i++)
		cout << A[i] << endl;
}

/* A Sample Output 
=================================================================
Harper CSC122-S01 by Mr. Jin Guo: Assignment #6, Spring 2021
Student: <Your Name>

This program will read a name list from a file, sort the list and
then write the sorted list to another file.
=================================================================

Please enter the file name of the name list ==> h6_10names_in.txt

>>> This is the original name list in the file:
___________________________
Sean Peterson
Alicia Tosh
Ena Dillard
Mikki Brinkley
Myrtie Roca
Mary Roca
Tuyet Currin
Sylvia Jacinto
Antoinette Saulter
Cecil Chien

>>> Put the last name first ...
___________________________
Peterson, Sean
Tosh, Alicia
Dillard, Ena
Brinkley, Mikki
Roca, Myrtie
Roca, Mary
Currin, Tuyet
Jacinto, Sylvia
Saulter, Antoinette
Chien, Cecil

>>> Sorting the name list ...
___________________________
Brinkley, Mikki
Chien, Cecil
Currin, Tuyet
Dillard, Ena
Jacinto, Sylvia
Peterson, Sean
Roca, Mary
Roca, Myrtie
Saulter, Antoinette
Tosh, Alicia

Please enter the file name for the sorted list ==> h6_10names_out.txt
Done! Please check the sorted name list in the file h6_10names_out.txt!

*/

/*
************************************************
* (C) Copyright by Jin Guo
*
* This program is free for my class students.
* For any other purpose of using this program,
* please ask for permission by sending email to:
* taiji.guo@gmail.com
************************************************
*/

