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
#include "rv32i_hart.h"
#include "cpu_single_hart.h"
#include <getopt.h>
#include <cstdio>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::hex;
using std::stoul;

/**
* Prints an appropriate “Usage” error message and “Pattern” to stderr and terminates the program 
**/
static void usage()
{
	cerr << "Usage: rv32i [-d] [-i] [-r] [-z] [-l exec-limit] [-m hex-mem-size] infile" << endl;
	cerr << "    -d show disassembly before program execution" << endl;
	cerr << "    -i show instruction printing during execution" << endl;
	cerr << "    -l maximum number of instructions to exec" << endl;
	cerr << "    -m specify memory size (default = 0x100)" << endl;
	cerr << "    -r show register printing during execution" << endl;
	cerr << "    -z show a dump of the regs & memory after simulation" << endl;
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
    uint32_t memory_limit = 0x100; 
    int opt;
    int execution_limit = 0;
    int dflag = 0;
    int iflag = 0;
    int rflag = 0;
    int zflag = 0;

    while((opt = getopt(argc, argv, "m:l:dirz")) != -1)
    {
        switch(opt)
        {
            case 'd':
                dflag = 1;
                break;

            case 'i':
                iflag = 1;
		        break;

            case 'r':
                rflag = 1;
                break;

            case 'z':
                zflag = 1;
                break;

            case 'l':
                execution_limit = stoul(optarg, nullptr, 0);
                break;
            
            case 'm':
                memory_limit = stoul(optarg, nullptr, 16);
                break;

            default:
                usage();
        }
    }

	if(optind >= argc)
        usage();

    memory mem(memory_limit);

    if(!mem.load_file(argv[optind]))
        usage();

    rv32i_hart sim(mem);
    cpu_single_hart cpu(mem);

    if(dflag == 1)
    {
        disassemble(mem);
        sim.reset();
    }

    if(iflag == 1)
        cpu.set_show_instructions(true);

    if(rflag == 1)
        cpu.set_show_registers(true);

    cpu.run(execution_limit);

    if(zflag == 1)
    {
        cpu.dump();
        mem.dump();
    }

    return 0;
}
