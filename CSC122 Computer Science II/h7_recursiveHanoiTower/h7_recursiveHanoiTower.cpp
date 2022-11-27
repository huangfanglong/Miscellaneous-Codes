/*
=========================================================================================
Course: Harper CSC122-S01 by Mr. Jin Guo, Spring 2021
Student Name: <Your Name>

Program name: Tower of Hanoi
Program description: 	
	This program calculates the minimum number of moves required to solve a 
	Tower of Hanoi puzzle. It also shows steps of moving to solve the puzzle.

Instructions:
	1. Run h7_JG.out on Unix/Ares. t is the finished executable. Your finished 
		program should perform the same as this one does. Imitate its prompts 
		and output.
	2. Refer to s11a_factorial.cpp and s11b_Fibonacci.cpp
		to define HanoiExpessN(), HanoiRecursiveN() and HanoiRecursiveSteps().
	3. The given program can compile but cannot link until after you defined the 
		above three functions.
	4. Submit only your .cpp file. Name your file properly as usual.
	
Notes:
	1. What is Tower of Hanoi puzzle? Simply put the problem this way: given 
		three pegs, one with a set of N disks of decreasing size, determine the 
		minimum (optimal) number of steps it takes to move all the disks from their 
		initial position to a single stack on another peg without placing a larger 
		disk on top of a smaller one. See the references below for detailed info 
		about Tower of Hanoi. Also, watch the video listed under "CS Videos" on Bb.

	2. Given n is number of disks and hanoi(n) is the minimum of moves for the puzzle.
		Then we have,
		1) Recursive definition
			hanoi(n) = 1, if n == 1
			hanoi(n) = 2 * hanoi(n - 1) + 1, if n > 1

		2) An explicit formula: hanoi(n) = 2^n - 1, for all n >= 1

	3. You may use pow(double x, double y) (from <cmath>) to do 2^n.
	4. Before you define the given functions, this program will compile but not link. 

References:
	1. CS121 CS Videos -> Some Interesting Algorithms -> Tower of Hanoi 8 Discs Optimal.
	2. The Tower of Hanoi consists of three rods, and a number of disks of different 
		sizes which can slide onto any rod. The puzzle starts with the disks in a neat 
		stack in ascending order of size on one rod, the smallest at the top. 
		The objective of the puzzle is to move the entire stack to another rod, obeying 
		the following simple rules:
		1) Only one disk can be moved at a time.
		2) Each move takes a top disk from one stack and places it on top of another stack.
		3) No disk may be placed on top of a smaller disk.

		With three disks, the puzzle can be solved in seven moves. The minimum number of 
		moves required to solve a Tower of Hanoi puzzle is 2^n - 1, where n is the number 
		of disks.
		https://en.wikipedia.org/wiki/Tower_of_Hanoi

Created: 10/29/2017 by Jin Guo
Updated: 3/10/2021 by Jin Guo. Adapted for this semester.
=========================================================================================
*/
#include <iostream> 
#include <string>
#include <cmath>		// for pow()

using namespace std; 

/**
The following functions calculate how many steps are needed for
a Hanoi Tower puzzle.
*/
int HanoiExpessN(int n);	// expressive version
int HanoiRecursiveN(int n);	// recursive version

/**
This function will print each step of moving disks for a given size of
Hanoi Tower puzzle in a recursive way.

@param n: the number of disks to be moved.
@param start: the peg holding disks to be moved.
@param target: the peg to which disks will be moved to.
@param temp: the auxiliary peg.
*/
void HanoiRecursiveSteps(size_t n, string start, string temp, string target);

int main()
{
	cout << "===================================================================\n";
	cout << "Harper CSC122-S01: Assignment #7, Spring 2021\n";
	cout << "Student: <Your Name>\n\n";	
	cout << "This program calculates the numbers of moving Tower Hanoi in both \n";
	cout << "explicit way and recursive method. Then the moving steps will be\n";
	cout << "shown.\n";
	cout << "===================================================================\n\n";

	const int upperN = 10; // upper bound
	int n;

	cout << ">>> Calculate the Tower Hanoi expressively ...\n";
	for (n = 0; n <= upperN; n++)
	  cout << "Hanoi(" << n << ") = " << HanoiExpessN(n) << endl;

	cout << "\n>>> Calculate the Tower Hanoi recursively ...\n";
	for (n = 0; n <= upperN; n++)
	  cout << "Hanoi(" << n << ") = " << HanoiRecursiveN(n) << "\n";

	cout << "\n>>> Show moving steps for Tower of Hanoi ...\n";
	for (int n = 1; n <= 4; n++)
	{
		cout << "\n==> Steps for " << n << " disk(s) for Tower of Hanoi:\n";
		HanoiRecursiveSteps(n, "peg1", "peg2", "peg3");
	}

	cout << endl;
} 

/* A Sample Output
===================================================================
Harper CSC122-S01: Assignment #7, Spring 2021
Student: <Your Name>

This program calculates the numbers of moving Tower Hanoi in both
explicit way and recursive method. Then the moving steps will be
shown.
===================================================================

>>> Calculate the Tower Hanoi expressively ...
Hanoi(0) = 0
Hanoi(1) = 1
Hanoi(2) = 3
Hanoi(3) = 7
Hanoi(4) = 15
Hanoi(5) = 31
Hanoi(6) = 63
Hanoi(7) = 127
Hanoi(8) = 255
Hanoi(9) = 511
Hanoi(10) = 1023

>>> Calculate the Tower Hanoi recursively ...
Hanoi(0) = 0
Hanoi(1) = 1
Hanoi(2) = 3
Hanoi(3) = 7
Hanoi(4) = 15
Hanoi(5) = 31
Hanoi(6) = 63
Hanoi(7) = 127
Hanoi(8) = 255
Hanoi(9) = 511
Hanoi(10) = 1023

>>> Show moving steps for Tower of Hanoi ...

==> Steps for 1 disk(s) for Tower of Hanoi:
Disk_1: peg1 --> peg3

==> Steps for 2 disk(s) for Tower of Hanoi:
Disk_1: peg1 --> peg2
Disk_2: peg1 --> peg3
Disk_1: peg2 --> peg3

==> Steps for 3 disk(s) for Tower of Hanoi:
Disk_1: peg1 --> peg3
Disk_2: peg1 --> peg2
Disk_1: peg3 --> peg2
Disk_3: peg1 --> peg3
Disk_1: peg2 --> peg1
Disk_2: peg2 --> peg3
Disk_1: peg1 --> peg3

==> Steps for 4 disk(s) for Tower of Hanoi:
Disk_1: peg1 --> peg2
Disk_2: peg1 --> peg3
Disk_1: peg2 --> peg3
Disk_3: peg1 --> peg2
Disk_1: peg3 --> peg1
Disk_2: peg3 --> peg2
Disk_1: peg1 --> peg2
Disk_4: peg1 --> peg3
Disk_1: peg2 --> peg3
Disk_2: peg2 --> peg1
Disk_1: peg3 --> peg1
Disk_3: peg2 --> peg3
Disk_1: peg1 --> peg2
Disk_2: peg1 --> peg3
Disk_1: peg2 --> peg3

*/

/*
 ************************************************
 * (C) Copyright by Jin Guo
 *
 * This program is free for my class students.
 * For any other purpose of using this program,
 * please ask for permission by sending email to:
 * taiji.guo@gmail.int
 ************************************************
*/

