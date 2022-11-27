[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=5504615&assignment_repo_type=AssignmentRepo)
### CSCI 340 - Data Structures and Algorithm Analysis

# Randomly Generated Integers

For this computer assignment, you are to write a C++ program to *generate random integers* in the range `LOW = 1`, `HIGH = 10000` and to store them in a `vector<int> v` of size `VEC_SIZE = 200`. Then sort the contents of the vector (in ascending order) and display it on stdout.
  
The program is partially implemented. You can obtain the source file `rgi.cc` within this Git repository.

To sort the contents of a vector, use the `sort()` function in the STL. In addition to the `main()` routine, include the following subroutines in your program:

- `void genRndNums(vector<int> &v, int num)` Initialize the random number generator (RNG) by calling the function `srand (SEED)` with the seed value `SEED = 1`, generate `num` random integers by calling the function `rand()`, and store them in `vector v` using `v.push_back()`.

- `void printVec(const vector<int> &v)` Displays the contents of `vector v` on stdout by printing exactly `NO_ITEMS = 12` numbers on each line, except perhaps the last line. Print each number, right-aligned, using `ITEM_W = 5` spaces on stdout.

**Programming Notes:**

- Your source file are named `rgi.cc` and your header file is `rgi.h`. Guard the statements in your header file using the following format. (This is necessary because you don't want the statements in a header file processed more than once.)

```c++
#ifndef H_RGI // should not be defined any place else 
#define H_RGI // same const value as for ifndef directive

// put all statements for your header file here

#endif
```

- Inlcude ONLY those header files in your `rgi.h` file that are needed by the declarations in your header file.

- Include any other header files (that are needed in your program) in your `rgi.cc` program file. For example, to gain access to the `iostream` library, which defines a set of simple I/O operations, insert the line `#include <iostream>` in your header file, to gain access the I/O manipulators such as `setw`, insert the line `#include <iomanip>` in your header file; to access the vector container in the STL, insert the line `#include <vector>` in your header file; and to use the functions in the STL such as sort, insert the line `#include <algorithm>` in your header file. At the top of `rgi.cc`, we have inserted your header file `#include "rgi.h"`.
 
- You are not allowed to use any I/O functions from the C library, such as `scanf` or `printf`. Instead, use the I/O functions from the C++ library, such as `std::cin` or `std::cout`.

- Add documentation to your source file(s) as discussed in lecture and on the course web pages.

- We have included a `Makefile` for your reference, in future assignments you will need to build your own. To compile your code just type `make` in the project directory. To test your program, execute `./rgi &> rgi.out`, which will put the output (including any error messages) in file `rgi.out`. You can find the correct output of this program in file `rgi.refout`, you can compare the two files by using `diff` on turing or hopper, `diff rgi.out rgi.refout`, if the files are the same there will be no output from `diff`.

When your program is ready for grading, ***commit*** and ***push*** your local repository to remote git classroom repository and follow the _**Assignment Submission Instructions**_.
