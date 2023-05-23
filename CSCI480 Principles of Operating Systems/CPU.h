/********************************************************
 * CSCI 480 MidOS Project
 * 
 * Julia Finegan
 * Long Huang
 * Brandon Romito
 * David Ostman
 * Gurpreet Girn
**********************************************************/

#ifndef CPU_H
#define CPU_H


#include "MMU.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <assert.h>
#include <string>
#include "PCB.h"

using namespace std;

/**
 * @brief Read and execute instruction opcodes
 *
 * *******************************************************************/
class  CPU
{
    
protected :
    PCB current_process ;     // Regs that will contain will all be uninitialized at first
    MMU &mem;        // Mem from which instructions are found

public :
    /**
     * @brief Initializes CPU with memory
     * @param m the memory object
     * *************************************************************/
    CPU ( MMU &m) : mem ( m) { }

    /**
     * @brief sets pc to 0, resets the regs, insn counter to 0, halt
     * to false and reason to non
     * *************************************************************/
    void reset () ;
    void run();
    void exec (string insn) ;

private :    

    void exec_incr(int arg1, int arg2);                 ///< Increment register by 1
    void exec_addi(int arg1, int arg2);                 ///< Add constant to register
    void exec_addr(int arg1, int arg2);                 ///< Add 2nd register to 1st register
    void exec_pushr(int arg1, int arg2);                ///< Push register onto stack
    void exec_pushi(int arg1, int arg2);                ///< Push constant onto stack
    void exec_movi(int arg1, int arg2);                 ///< Set constant to register
    void exec_movr(int arg1, int arg2);                 ///< Set 2nd register to 1st register
    void exec_movmr(int arg1, int arg2);                ///< Set r1 to what at address in r2
    void exec_movrm(int arg1, int arg2);                ///< move r2 to address in r1
    void exec_movmm(int arg1, int arg2);                ///< move what at address in r2 to what at address in r1
    void exec_printr(int arg1, int arg2);               ///< Display contents of given register
    void exec_printm(int arg1, int arg2);               ///< Displays contents of memory whose address is in register 1
    void exec_jmp(int arg1, int arg2);                  ///< control transfers to the instruction whose address is r1 bytes relative to the current instruction. R1 may be negative.
    void exec_cmpi(int arg1, int arg2);                 ///< If rx < y, set sign flag. If rx > y, clear sign flag. If rx == y , set zero flag.
    void exec_cmpr(int arg1, int arg2);                 ///< The same as cmpi except now both operands are registers.
    void exec_jlt(int arg1, int arg2);                  ///<  if the sign flag is set, jump to the instruction whose offset is rx bytes from the current instruction.
    void exec_jgt(int arg1, int arg2);                  ///< if the sign flag is clear, jump to the instruction whose offset is rx bytes from the current instruction
    void exec_je(int arg1, int arg2);                   ///< if the zero flag is clear, jump to the instruction whose offset is rx bytes from the current instruction.
    void exec_call(int arg1, int arg2);                 ///< call the procedure at offset r1 bytes from the current instruction. The address of the next instruction to execute after a return is pushed on the stack.
    void exec_callm(int arg1, int arg2);                ///< call the procedure at offset [r1] bytes from the current instruction. The address of the next instruction to execute after a return is pushed on the stack.
    void exec_ret(int arg1, int arg2);                  ///< Pop the return address from the stack and transfer control to this instruction.
    void exec_alloc(int arg1, int arg2);                ///< allocate memory of size equal to r1 bytes and return the address of the new memory in r2. If failed, r2 is cleared to 0.
    void exec_acquirelock(int arg1, int arg2);          ///< Acquire the operating system lock whose # is provided in the register r1. If the lock is invalid, the instruction is a no-op.
    void exec_releaselock(int arg1, int arg2);          ///< release the operating system lock whose # is provided in the register r1; if the lock is not held by the current process, the instruction is a no-op.
    void exec_sleep(int arg1, int arg2);                ///<  Sleep the # of clock cycles as indicated in r1. Another process or the idle process must be scheduled at this point. If the time to sleep is 0, the process sleeps infinitely.
    void exec_setpriority(int arg1, int arg2);          ///< Set the priority of the current process to the value in register r1; See priorities discussion in Operating system design
    void exec_exit(int arg1, int arg2);                 ///<  This opcode is executed by a process to exit and be unloaded. Another process or the idle process must now be scheduled.
    void exec_freememory(int arg1, int arg2);           ///< Free the memory allocated whose address is in r1.
    void exec_mapsharedmem(int arg1, int arg2);         ///< Map the shared memory region identified by r1 and return the start address in r2.
    void exec_signalevent(int arg1, int arg2);          ///< Signal the event indicated by the value in register r1.
    void exec_waitevent(int arg1, int arg2);            ///< Wait for the event in register r1 to be triggered. This results in context-switches happening.
    void exec_input(int arg1, int arg2);                ///< read the next 32-bit value into register r1.
    void exec_memoryclear(int arg1, int arg2);          ///< set the bytes starting at address r1 of length r2 bytes to zero.
    void exec_terminateprocess(int arg1, int arg2);     ///< terminate the process whose id is in the register r1.
    void exec_popr(int arg1, int arg2);                 ///< pop the contents at the top of the stack into register rx which is the operand. Stack pointer is decremented by 4.
    void exec_popm(int arg1, int arg2);                 ///< pop the contents at the top of the stack into the memory operand whose address is in the register which is the operand. Stack pointer is decremented by 4.


    int get_num_arg(string arg);
    void parse_insn(string insn, int &opcode, int &arg1, int &arg2);

    bool halt = { false };  // be set to false when execution needs to end
    std::string halt_reason = {"none"};  // reason that program ended 

    int insn_counter = { 0 };  // number instruction executed
    int pc = { 0 };    // current address of program

	// Define the execute pointer that point to corresponding opcode by value (array)
    typedef void (CPU::*exec_ptr)(int, int); 
    
    exec_ptr exec_ptr_arr[37] = 
    {
		nullptr, 
		&CPU::exec_incr, 				
		&CPU::exec_addi, 		
		&CPU::exec_addr, 		
		&CPU::exec_pushr,		
		&CPU::exec_pushi,
		&CPU::exec_movi, 				
		&CPU::exec_movr, 		
		&CPU::exec_movmr,		
		&CPU::exec_movrm, 		
		&CPU::exec_movmm, 
        &CPU::exec_printr, 				
        &CPU::exec_printm, 		
        &CPU::exec_jmp, 		
        &CPU::exec_cmpi,  		
        &CPU::exec_cmpr, 
		&CPU::exec_jlt, 				
		&CPU::exec_jgt, 		
		&CPU::exec_je, 			
		&CPU::exec_call,  		
		&CPU::exec_callm,
        &CPU::exec_ret,					
        &CPU::exec_alloc, 		
        &CPU::exec_acquirelock, 
        &CPU::exec_releaselock, 
        &CPU::exec_sleep, 
        &CPU::exec_setpriority, 		
        &CPU::exec_exit, 		
        &CPU::exec_freememory, 	
        &CPU::exec_mapsharedmem,
        &CPU::exec_signalevent, 		
        &CPU::exec_waitevent, 	
        &CPU::exec_input, 		
        &CPU::exec_memoryclear, 
        &CPU::exec_terminateprocess, 	
        &CPU::exec_popr, 				
        &CPU::exec_popm
	};
};

#endif