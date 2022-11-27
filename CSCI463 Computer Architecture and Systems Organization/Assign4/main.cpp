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

#include "memory.h"
#include "rv32i_decode.h"
#include <getopt.h>
#include <sstream>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::hex;

/**
* Prints an appropriate “Usage” error message and “Pattern” to stderr and terminates the program 
**/
static void usage()
{
	cerr << "Usage: rv32i [-m hex-mem-size] infile" << endl;
	cerr << "    -m specify memory size (default = 0x100)" << endl;
	exit(1);
}

/**
* Decode and print each instruction in a loop
* 
* @param mem The memory for output and decode
**/
static void disassemble(const memory &mem)
{
	uint32_t memAddress = 0;
	uint32_t insn = 0;
	// Rendered(decoded) instruction
	string renderedInsn;

	// Divide every byte in memory by 4 because each insn is 4 bytes
	for (unsigned i = 0; i < mem.get_size() / 4; i++)
	{
		// Set the instruction to the instruction at the memory's address
		insn = mem.get32(memAddress);
		// Decode the instruction at the memory's address
		renderedInsn = rv32i_decode::decode(memAddress, insn);

		cout << hex::to_hex32(memAddress) << ": " << hex::to_hex32(insn) << "  " << 
	    renderedInsn << std::endl;

		// Increment memory address to next instruction
		memAddress += 4;
	}
}


/**
* Call the functions to load and disassemble binary RV32i instructions, code provided by professor
*
* @param argc argument count
* @param argv argument values
* 
 **********************************************************************************************/
int main(int argc, char **argv)
{
	uint32_t memory_limit = 0x100; // default memory size = 256 bytes
	int opt;
	while ((opt = getopt(argc, argv, "m:")) != -1)
	{
		switch (opt)
		{
			case 'm':
			{
				std::istringstream iss(optarg);
				iss >> std::hex >> memory_limit;
			}
			break;
			default: /* ’?’ */
			usage();
		}
	}
	if (optind >= argc)
		usage(); // missing filename
		
	memory mem(memory_limit);
	
	if (!mem.load_file(argv[optind]))
		usage();
	
	disassemble(mem);
	mem.dump();
	
	return 0;
}
