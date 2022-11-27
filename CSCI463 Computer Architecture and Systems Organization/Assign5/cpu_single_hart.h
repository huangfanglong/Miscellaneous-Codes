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

#ifndef CPU_H
#define CPU_H

#include "hex.h"
#include "rv32i_decode.h"
#include "rv32i_hart.h"
#include "registerfile.h"

/**
 * A subclass of rv32i_hart that is used to represent a CPU with a single hart
 * 
 **********************************************************************************************/
class cpu_single_hart : public rv32i_hart
{
	public:
	/**
	 * Constructor to pass the memory class instance to the constructor in the base class
	 * */
		cpu_single_hart(memory &mem) : rv32i_hart(mem) {}
		
		void run(uint64_t exec_limit);		
};
#endif
