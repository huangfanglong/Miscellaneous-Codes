[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=5688710&assignment_repo_type=AssignmentRepo)
### CSCI 340 - Data Structures and Algorithm Analysis

# Sieve of Eratosthenes

For this computer assignment, you are to write and implement an interactive C++ program to find and print all prime numbers, which are less than or equal to a given value of **n**, using the algorithm known as the *Sieve of Eratosthenes*.

A prime number **p** is an integer greater than **1** that is divisible only by **1** and **p** (itself). The algorithm begins by initializing a set container to contain all the integers in the range **2** to **n**. A loop makes multiple passes over the elements in the set, using successive integer key values 2, 3, 4, ... Each pass *shakes free* nonprime numbers and lets them *filter through the sieve*. At the end, only the prime numbers remain.

Begin with the integer `m = 2`, which is the smallest prime number. The pass scans the set and removes all multiples of 2, having the form `2 * k` for `k >= 2`. The multiples cannot be prime numbers, because they are divisible by 2. 

At the end of the pass, we have removed all even numbers except 2. Next, look at the integer `m = 3`, which is a prime number. As with value `2`, remove all multiples of 3, having the form `3 * k` for `k >= 3`. The multiples 12, 18, and so forth, are even numbers, so they have already been removed from the set. 

The next key integer is `m = 4`, which is no longer in the set, because it was removed as a multiple of 2. The pass takes no action. The process continues until it removes all multiples of prime numbers. In other words, for integer m, remove all multiples of m, having the form `m * k` for `k >= m`. The numbers that remain in the sieve are the prime numbers in the range 2 to n.

The algorithm uses an optimization feature by looking at the key values for `m <= sqrt(n)`. However, in your implementation, test all numbers m such that `m * m <= n`, rather than computing the square root of n.

Starter code for `sieve.cc` is provided for you as part of this repository, it contains the main function. You will then need to add additional code to the `main()` routine. This code will create an empty set of integers, prompt the user for the upper limit of numbers that you will search for prime numbers and then call the subroutine `sieve()` to execute the *Sieve of Eratosthenes*. The main then calls the subroutine `print_primes()` to print the prime numbers on stdout.

Use a set container to store the prime numbers. In the STL, a set is implemented as an associative container, it uses the model of a mathematical set, it stores keys that are objects of a specified data type, where duplicate keys are not allowed. To use a set in your program, you need to insert the statement `#include <set>` which is already defined in `sieve.cc`.

In addition to adding code to `main()`, you are required to implement the following functions:

- `void sieve(set<int> &s, int n)`: This routine can be used to apply the *Sieve of Eratosthenes* algorithm to remove all nonprime numbers from the integer set `s = {2, 3, ..., n}`.

- `void print_primes(const set<int> &s)`: This routine can be used to print the elements in the integer set `s` with `NO_ITEMS = 16` primes per line and `ITEM_W = 5` spaces allocated for each prime.

**Programming Notes:**

* Include any necessary headers and add necessary global constants. 

* You are not allowed to use any I/O functions from the C library, such as `scanf` or `printf`. Instead, use the I/O functions from the C++ library, such as `cin` or `cout`.

* Add documentation to the appropriate your source files as discussed in lecture.

* You can find a sample results file, `sieve.refout` for input of 2000.

* Prepare your Makefile (**you need to construct and add Makefile**) so that the TA only needs to invoke the command `make` to compile your source file and produce the executable file `sieve`.  Make sure you use exactly the same file names specified here, i.e. `sieve.cc` and `sieve`, in your `Makefile`. Otherwise your submission will get 0 points.

When your program is ready for grading, ***commit*** and ***push*** your local repository to remote git classroom repository and follow the _**Assignment Submission Instructions**_.
