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
#include <string>
#include <unordered_map>
#include "PCB.h"

using namespace std;

// PCB constructor
PCB::PCB(int processID, int virtual_memory_size, int page_size, const vector<string>& instructions, string diskName)
{
    m_pointer = nullptr;
    m_state = ProcessState::NEW;
    m_processID = processID;
    m_programCounter = 0;
    m_registers = vector<int>(12);
    m_instructions = instructions;
    m_diskName = diskName;

    // Initialize page table with empty pages
    for (int i = 0; i < virtual_memory_size / page_size; i++) 
    {
        m_pageTable[i] = -1;
    }
}

void PCB::resetRegisters()
{
    m_registers.clear();
    for(int i = 0; i <= NUM_REGS; i++)
        m_registers.push_back(0);
}

//Getter
char* PCB::getPointer() const 
{ 
    return m_pointer; 
}
ProcessState PCB::getState() const 
{ 
    return m_state; 
}
int PCB::getProcessNumber() const 
{ 
    return m_processNumber; 
}
int PCB::getProcessID() const 
{ 
    return m_processID; 
}
int PCB::getProgramCounter() const 
{ 
    return m_programCounter; 
}
int PCB::getRegister(int index) const 
{ 
    return m_registers[index]; 
}
string PCB::getInstruction(int index) const
{ 
    return m_instructions[index];
}
vector<string> PCB::getInstructions() const
{
    return m_instructions;
}
string PCB::getDiskName() const
{
    return m_diskName;
}
int PCB::getMemoryLimit() const 
{ 
    return m_memoryLimit; 
}


//Setters
void PCB::setPointer(char* pointer)
{
    m_pointer = pointer;
}
void PCB::setState(ProcessState state)
{
    m_state = state;
}
void PCB::setProcessID(int processID)
{
    m_processID = processID;
}
void PCB::setProgramCounter(int programCounter)
{
    m_programCounter = programCounter;
}
void PCB::setRegister(int index, int value)
{
    m_registers[index] = value;
}
void PCB::setInstructions(int index, std::string value)
{
    m_instructions[index] = value;
}
// void PCB::setdiskName(int index, std::string value)
// {
//     m_diskName[index] = value;
// }

// Get the physical address of a page in the page table
int PCB::getPhysicalAddress(int pageNumber) const 
{
    if (m_pageTable.count(pageNumber) > 0) 
    {
        return m_pageTable.at(pageNumber);
    }
    std::cout << "Error: Page " << pageNumber << " not found in page table" << std::endl;
    return -1;
}

// Set the physical address of a page in the page table
void PCB::setPhysicalAddress(int pageNumber, int physicalAddress) 
{
    m_pageTable[pageNumber] = physicalAddress;
}

int PCB::getPageTableSize() {return m_pageTable.size();}

void PCB::setPriority(int p)
{
    priority = p;
}