/********************************************************
 * CSCI 480 MidOS Project
 * 
 * Julia Finegan
 * Long Huang
 * Brandon Romito
 * David Ostman
 * Gurpreet Girn
**********************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"
#include "MMU.h"

using std::vector;
using namespace std;


int MMU::getSize()
{
	return virtual_memory_size;
}

int MMU::read(int virtual_address) 
{
    int page_number = virtual_address / page_size;						// Determines which page of virtual memory the address is in (e.g: virtual address 16 KB / page size of 4 KB = page number 4)
    
    if(!virtual_frames[page_number])
        handlePageFault(page_number);
    int offset = virtual_address % page_size;						// Calculates the offset (distance from beginning of the page to the current page_number), which is the remainder the page_number above
    int physical_address = current_process.getPhysicalAddress(page_number) * page_size + offset;			// Find the physical address. page_table[page_number] represents the frame number(index) in physical memory.
                                            // The frame number * size of the page gives the starting address of physical frame in physical memory. Then we use the offset to
                                            // locate the exact location
                                                                                    
    if (physical_address >= 0 && physical_address < PHYSICAL_MEM_SIZE) 			// Check if the physical address is within physical memory
    {
        return physical_memory[physical_address];						// Return what is in the physical address
    } 
    
    else 											// Else physical address not within physical memory, page fault
    {
        page_faults++;									// Add one to the number of page fault(s)
        handlePageFault(page_number);							// Call function handlePageFault to allocate a new empty frame to the page number
        return physical_memory[current_process.getPhysicalAddress(page_number) * page_size + offset];		// Return what is in the physical address after allocating new frame to page
    }
}

/**
*	The write function translates the virtual address to a physical address and write/set/update a specified value to that address using Demand Paging technique.
*	
*	@param virtual_address is the input/specified virtual address to write to
*	@param input_value is the value that is to be written/set to the specified virtual address parameter
**/   
void MMU::write(int virtual_address, int input_value) 
{
    int page_number = virtual_address / page_size;							// Calculates the page number of the virtual address (the page of virtual memory the address is in)
    
    if(!virtual_frames[page_number])
        handlePageFault(page_number);
    int offset = virtual_address % page_size;							// Calculates the offset (distance from beginning of the page to the current page_number), which is the remainder the page_number above
    int physical_address = current_process.getPhysicalAddress(page_number) * page_size + offset;				// Find the physical address; page_table[page_number] represents the frame number in physical memory that contains the page. 
                                                // The frame number * size of the page gives the starting address of physical frame in physical memory. Then we use the offset to
                                                // locate the exact location
    
    if (physical_address >= 0 && physical_address < PHYSICAL_MEM_SIZE)				// Check if the physical address is within physical memory
    {
        physical_memory[physical_address] = input_value;						// Update/write the specified input value to the physical address
    } 
    
    else 												// Else physical address not within physical memory, page fault
    {
        page_faults++;										// Add one to the number of page fault(s)
        handlePageFault(page_number);								// Call function handlePageFault to allocate a new empty frame to the page number
        physical_memory[physical_address] = input_value;						// Update the value 
    }
}

/**
*	Return the number of page faults
*	
*	@return the number of page faults
**/ 
int MMU::getPageFaults() { return page_faults; }

/**
*	Generic and simple function to handle page faults by allocating a new empty frame to the page
*	
*	@param page_number is the virtual page number that is causing the page fault
**/ 
void MMU::handlePageFault(int page_number) 
{
    // Loop through the page table to look for an empty frame
    // (Remember constructor page_table(PHYSICAL_MEM_SIZE_input / page_size_input) above)
    int memStart = current_process.getProcessID() * (PHYSICAL_MEM_SIZE / num_processes);
    int memEnd = memStart + (PHYSICAL_MEM_SIZE / num_processes);

    for (int i = memStart; i < memEnd; i++) 
    {
        if (current_process.getPhysicalAddress(i) == -1)				// If the frame is empty (indicated by '-1' as above)
        {
            current_process.setPhysicalAddress(page_number, i);		// Replace the frame with the new empty frame
            FrameProcess addFrame = {page_number, current_process};
            //addFram.frame_number = page_number;
            //addFrame.process = current_process;
            nextMemFrame.push(addFrame);
            break;
        }

        if(i == ((PHYSICAL_MEM_SIZE / page_size) - 1))
        {
            FrameProcess nextFrame = nextMemFrame.front();
            nextMemFrame.pop();
            writeTodisk(nextFrame.process.getDiskName(), nextFrame.frame_number);

            readFromdisk(current_process.getDiskName(), page_number, nextFrame.frame_number);
        }

    }
}

void MMU::loadCurrentPCB(PCB p){ current_process = p;}

void MMU::readFromdisk(string diskName, int pageNum, int location)
{
    ifstream data(diskName, ifstream::binary);
    char* buffer = new char[16];

    if(data)
    {
        data.seekg(pageNum*16, ios::beg);
        data.read(buffer, 16);

        for(int i = 0; i < 16; i++)
        {
            physical_memory[location + i] = atoi(&buffer[i]);
        }

        current_process.setPhysicalAddress(pageNum, location/16);

        data.close();
    }

}

void MMU::writeTodisk(string diskName, int location)
{
    auto first = physical_memory.begin() + (location * 16);
    auto last = physical_memory.begin() + (location * 16) + 16;
    vector<char> buffer(first, last);
    char * frame = &buffer[0];

    ofstream data;
    data.open(diskName, ios::out | ios::binary);

    data.seekp(location);
    data.write(frame, 16);

    data.close();
}

/**
*	Create a process within the virtual machine
*	
*	@param pages is the number of pages to be allocated to the new process
**/ 
void MMU::createProcess(int virtual_memory_size, const vector<string> instructions, string name) 
{
    int process_id = process_counter++;			// Increment process counter and use its value as process ID
    PCB new_pcb = {process_id, virtual_memory_size, page_size, instructions, name};	// Pass in parameters to create a new PCB object
                                                    // process_id is the ID of this process initialized and assigned above for this object
                                                    // vector<int> creates a page table for this process, initialized all entries with '-1' to indicate that it's empty and no pages have been allocated yet
                                                    // The '0' initializes the PagesUsed field in the ProcessControlBlock struct since the process has not yet been allocated any pages

    new_pcb.setRegister(8, process_id);
    process_table.push_back(new_pcb);
}

/**
*	Allocate memory to a process
*	
*	@param process_id is the ID of the process to be allocated memory
*	@param pages is the number of pages to be allocated to the new process
**/ 
int MMU::allocateMemoryToProcess(int process_id, int pages) 
{
    PCB provided_process = process_table[process_id];
    int address = -1;
	for (int i = 0; i < provided_process.getPageTableSize(); i++) 	// Iterate through page_table to find free frames (indicated by '-1')
	{
		if (provided_process.getPhysicalAddress(i) == -1) 
		{
            address = i;

            for(int j = i; j < i+pages; j++)
            {
                if(provided_process.getPhysicalAddress(j) != -1)
                {
                    writeTodisk(provided_process.getDiskName(), j);
                    provided_process.setPhysicalAddress(j, -1);
                }
            }

            break;
			
		}
        
	}

    return address;
}

