/********************************************************
 * CSCI 480 MidOS Project
 * 
 * Julia Finegan
 * Long Huang
 * Brandon Romito
 * David Ostman
 * Gurpreet Girn
**********************************************************/

#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

enum class ProcessState 
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class PCB 
{
public:

    PCB(int processID,int virtual_memory_size, int page_size, const vector<string>& instructions, string diskName);
    
    PCB() {};
    void resetRegisters();

    //Getter
    char* getPointer() const; 

    ProcessState getState() const; 

    int getProcessNumber() const; 

    int getProcessID() const; 

    int getProgramCounter() const; 

    int getRegister(int index) const; 

    string getInstruction(int index) const;

    vector<string> getInstructions() const;

    string getDiskName() const;

    int getMemoryLimit() const;

    // Get the physical address of a page in the page table
    int getPhysicalAddress(int pageNumber) const; 

    int getPageTableSize();

    int getPriority() {return priority;};


    //Setters
    void setPointer(char* pointer);

    void setState(ProcessState state);

    void setProcessID(int processID);

    void setProgramCounter(int programCounter);

    void setRegister(int index, int value);

    void setInstructions(int index, std::string value);

    // Set the physical address of a page in the page table
    void setPhysicalAddress(int pageNumber, int physicalAddress); 

    void setPriority(int p);

private:

    static const int NUM_REGS = 12; // REG 11 is sign flag, REG 12 is zero flag
    char* m_pointer;
    int priority;
    ProcessState m_state;
    int m_processNumber;
    int m_processID;
    int m_programCounter;
    std::vector<std::string> m_instructions;
    string m_diskName;
    std::vector<int> m_registers;
    int m_memoryLimit;
    std::unordered_map<int, int> m_pageTable; // maps page number to physical address
};

#endif