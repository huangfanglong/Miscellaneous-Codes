/********************************************************
 * CSCI 480 MidOS Project
 * 
 * Julia Finegan
 * Long Huang
 * Brandon Romito
 * David Ostman
 * Gurpreet Girn
**********************************************************/

#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"

using std::vector;
using namespace std;

// Notes:	virtual  memory = pages
//		physical memory = frames
//
// Resources used are cited at the end.

/**
*	The Memory Management Unit encapsulation handles the mapping between the Virtual Memory and Physical Memory (translating virtual <-> phys. address)
*
**/

struct FrameProcess {
		int frame_number;
		PCB process;
	};

class MMU 
{
private:
    const int PHYSICAL_MEM_SIZE = 400;
    vector<bool> virtual_frames;					// Array holds the frames of physical memory and whether they are valid or not	
    vector<int> physical_memory;				// Represents physical memory of the virtual machine. Each index represents a frame in physical memory, which stores content read or write from virtual memory.
    int virtual_memory_size;					
    int page_size;
    int page_faults;
	PCB current_process;
	int free_frames;							// Pool of free frames
	queue<FrameProcess> nextMemFrame;// = new queue<FrameProcess>();
	int num_processes;
	vector<PCB> process_table;// = new vector<PCB>();			// Store PCB process(es) objects currently running in the Virtual Machine.
														// Each entry represents a process and stores their corresponding processID and PagesUsed as well as the process's page table
	int process_counter;						// Keep track of number of processes; is used to point at the current process number (ID) in our virtual machine


public:

	/**
	*	Constructor
	*	Usage: MMU mmu(virtual_memory_size_input, page_size_input)
	*
	*	@param virtual_memory_size_input is the specified size of physical memory
	*	@param page_size_input is the specified size of a page
	**/

	
	MMU(int virtual_memory_size_input, int page_size_input, int numProcesses)
	{
		
		for(int i = 0; i < (PHYSICAL_MEM_SIZE / page_size_input); i++)
			virtual_frames.push_back(false);
		for(int i = 0; i < (PHYSICAL_MEM_SIZE); i++)
			physical_memory.push_back(-1);

		virtual_memory_size = virtual_memory_size_input;
		page_size = page_size_input;
		page_faults = 0;
		free_frames = PHYSICAL_MEM_SIZE / page_size;
		num_processes = numProcesses;
		nextMemFrame = {};
		process_table = {};
		process_counter = 0;
	};
	
	int getSize();

	/**
	*	The read function translates the virtual address to physical address and return the value at that physical address using Demand Paging technique.
	*
	*	@param virtual_address is the input/specified virtual address to read from
	*
	*	@return return the value/data that is in the corresponding physical address specified by the virtual address
	**/
    int read(int virtual_address); 


	/**
	*	The write function translates the virtual address to a physical address and write/set/update a specified value to that address using Demand Paging technique.
	*	
	*	@param virtual_address is the input/specified virtual address to write to
	*	@param input_value is the value that is to be written/set to the specified virtual address parameter
	**/   
    void write(int virtual_address, int input_value); 

    
	/**
	*	Return the number of page faults
	*	
	*	@return the number of page faults
	**/ 
    int getPageFaults();
	
	/**
	*	Generic and simple function to handle page faults by allocating a new empty frame to the page
	*	
	*	@param page_number is the virtual page number that is causing the page fault
	**/ 
    void handlePageFault(int page_number); 
	
	// Loads the next PCB for the current process
	void loadCurrentPCB(PCB p);

	// Used for demand paging to get memory from disk and add to physcial memory
	void readFromdisk(string diskName, int pageNum, int location);

	// Used for demand paging to remove from physical memory and write it to the disk
	void writeTodisk(string diskName, int location);

	// gets the process table at given index
	PCB getProcess(int i) {return process_table[i];};

	// returns the number of processes being managed
	int getNumProcesses() {return num_processes;};

	// Return the current process
	PCB getCurrentProcess() {return current_process;};

	// Sets the current process
	void setCurrentProcess(PCB process) {current_process = process;};

	/**
	*	Create a process within the virtual machine
	*	
	*	@param pages is the number of pages to be allocated to the new process
	**/ 
    void createProcess(int virtual_memory_size, const vector<string> instructions, string name);

	/**
	*	Allocate memory to a process
	*	
	*	@param process_id is the ID of the process to be allocated memory
	*	@param pages is the number of pages to be allocated to the new process
	**/ 
	int allocateMemoryToProcess(int process_id, int pages); 




    
};

/*
*	Resources used:
*
*	What is Virtual Memory? MMU, Page Tables, and more! 	- 	https://youtu.be/4e18yybPo1E
*	Paging A Memory Management Technique			-	http://www2.cs.uregina.ca/~hamilton/courses/330/notes/memory/paging.html
*	CS 4410 Operating Systems Memory: Paging		-	https://www.cs.cornell.edu/courses/cs4410/2016su/slides/lecture11.pdf	(page 6 for calculating physical address equation)
*	Abraham Silberschatz 					- 	Operating-System Concepts 10th Edition, 2018 => Chapter 10, page 392+
*	Stackoverflow/exchanges, etc
*/

#endif