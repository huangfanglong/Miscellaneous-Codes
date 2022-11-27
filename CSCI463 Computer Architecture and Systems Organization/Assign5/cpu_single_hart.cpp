//***************************************************************************
//
//  Long Huang
//  Z1942308
//  20228-CSCI-463-1
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************

#include "cpu_single_hart.h"

/**
 * Run the simulator with a given execution limit
 * 
 * @param exec_limit is the execution limit of the simulator
 * 
 * @return true or exec_limit number of instructions have been executed
 * 
 **********************************************************************************************/
void cpu_single_hart::run(uint64_t exec_limit)
{
	regs.set(2, mem.get_size());
	
	// If the exec_limit parameter is zero, call tick() in a loop until the is_halted() returns true
	// If the exec_limit parameter is not zero then enter a loop that will call tick() until is_halted()
	// 		returns true or exec_limit number of instructions have been executed.
	while((is_halted() != true && exec_limit == 0) || (is_halted() != true && get_insn_counter() < exec_limit ))
	{
		tick();
	}

	if(is_halted())
	{
		std::cout << "Execution terminated. Reason: " << get_halt_reason() << std::endl;
	}

	std::cout << get_insn_counter() <<  " instructions executed" << std::endl;
}

