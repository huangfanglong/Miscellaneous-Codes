/********************************************************
 * CSCI 480 MidOS Project
 * 
 * Julia Finegan
 * Long Huang
 * Brandon Romito
 * David Ostman
 * Gurpreet Girn
**********************************************************/

#include "CPU.h"
#include "PCB.h"
#include <iostream>
#include <iomanip>

using namespace std;


void CPU::run()
{
    for(int i = 0; i < mem.getNumProcesses(); i++)
	{
        current_process = mem.getProcess(i);
        pc = 0;
        mem.setCurrentProcess(current_process);
        vector<string> process_instructions = current_process.getInstructions();
		while(pc < (int) process_instructions.size())
		{
			this->exec(process_instructions[pc]);
		}
	}
}

void CPU::exec(string insn)
{
    int opcode, arg1, arg2;

    //cout << insn << endl;

	// Parse the instruction into opcode, arg1 and arg2
    parse_insn(insn, opcode, arg1, arg2);

    (this->*exec_ptr_arr[opcode])(arg1, arg2);
    insn_counter++;
}

int CPU::get_num_arg(string arg)
{
    for(int i = arg.length()-1; i >= 0; i--)
    {
        if(arg[i] == ',')
            arg.erase(i, arg.length()-i);
        else if(arg[i] == '$' or arg[i] == ' ' or arg[i] == 'r')
            arg.erase(i, 1);
    }

    if(isdigit(arg[0]))
        return stoi(arg);
    return 0;
}

void CPU::parse_insn(string insn, int &opcode, int &arg1, int &arg2)
{
    // default values
    string args[] = {"0", "x0", "x0"};

    // Parse instruction into opcode and args.
    size_t start = 0;

    size_t pos = 0;
    for(int i = 0; pos != string::npos && i <= 2; i++) {
        pos = insn.find_first_of("r$", pos+1);
        args[i] = insn.substr(start, pos);
        start = pos;
    }

    opcode = get_num_arg(args[0]);
    switch(opcode)
    {
	case 27:
		arg1 = -1;
		arg2 = -1;
		break;
	case 6:
		arg1 = get_num_arg(args[1]);
		arg2 = get_num_arg(args[2]);
		break;
	case 11:
	case 23:
	case 24:
	case 25:
		arg1 = get_num_arg(args[1]);
		arg2 = -1;
		break;
	default:
		arg1 = get_num_arg(args[1]);
        arg2 = get_num_arg(args[2]);
		break;
    }
}

void CPU::reset ()
{
    pc = 0;
    current_process.resetRegisters();
    current_process.setRegister(10, mem.getSize()-1);
    insn_counter = 0;
    halt = false;
    halt_reason = "none";
}

void CPU::exec_incr(int arg1, int arg2)
{
    arg2 =  current_process.getRegister(arg1) + 1;
    current_process.setRegister(arg1, arg2);
    pc++;
}

void CPU::exec_addi(int arg1, int arg2)
{
    current_process.setRegister(arg1, current_process.getRegister(arg1) + arg2);
    pc++;
}

void CPU::exec_addr(int arg1, int arg2)
{
    int sum = current_process.getRegister(arg1) + current_process.getRegister(arg2);
    current_process.setRegister(arg1, sum);
    pc++;
}

void CPU::exec_pushr(int arg1, int arg2)
{
    mem.write(current_process.getRegister(10), current_process.getRegister(arg1));
    current_process.setRegister(10, current_process.getRegister(10) - 1);
    arg2 = arg2;
    pc++;
}

void CPU::exec_pushi(int arg1, int arg2)
{
    mem.write(current_process.getRegister(10), arg1);
    current_process.setRegister(10, current_process.getRegister(10) - 1);
    arg2 = arg2;
    pc++;
}

void CPU::exec_movi(int arg1, int arg2)
{
    current_process.setRegister(arg1, arg2);
    pc++;
}

void CPU::exec_movr(int arg1, int arg2)
{
    current_process.setRegister(arg1, current_process.getRegister(arg2));
    pc++;
}

void CPU::exec_movmr(int arg1, int arg2)
{
    current_process.setRegister(arg1, mem.read(current_process.getRegister(arg2)));
    pc++;
}

void CPU::exec_movrm(int arg1, int arg2)
{
    mem.write(current_process.getRegister(arg1), current_process.getRegister(arg2));
    pc++;
}

void CPU::exec_movmm(int arg1, int arg2)
{
    mem.write(current_process.getRegister(arg1), mem.read(current_process.getRegister(arg2)));
    pc++;
}

void CPU::exec_printr(int arg1, int arg2)
{
    cout << "process " << current_process.getProcessID() << " reg " << arg1 << ": " << current_process.getRegister(arg1) << endl;
    arg2 = arg2;
    pc++;
}

void CPU::exec_printm(int arg1, int arg2)
{
    cout << "Memory at " << current_process.getRegister(arg1) << ": " << mem.read(current_process.getRegister(arg1)) << endl;
    arg2 = arg2;
    pc++;
}

void CPU::exec_jmp(int arg1, int arg2)
{
    pc += current_process.getRegister(arg1);
    arg2 = arg2;
}

void CPU::exec_cmpi(int arg1, int arg2)
{
    int reg1 = current_process.getRegister(arg1);

    if(reg1 < arg2)
        current_process.setRegister(11, 1);
    else if(reg1 > arg2)
        current_process.setRegister(11,0);
    else
        current_process.setRegister(12, 1);

    pc++;
}

void CPU::exec_cmpr(int arg1, int arg2)
{
    int reg1 = current_process.getRegister(arg1);
    int reg2 = current_process.getRegister(arg2);

    if(reg1 < reg2)
        current_process.setRegister(11, 1);
    else if(reg1 > reg2)
        current_process.setRegister(11,0);
    else
        current_process.setRegister(12, 1);

    pc++;
}

void CPU::exec_jlt(int arg1, int arg2)
{
    if(current_process.getRegister(11))
        pc += current_process.getRegister(arg1);

    arg2 = arg2;
    pc++;
}

void CPU::exec_jgt(int arg1, int arg2)
{
    if(!current_process.getRegister(11))
        pc += current_process.getRegister(arg1);

    arg2 = arg2;
}

void CPU::exec_je(int arg1, int arg2)  
{
    if(!current_process.getRegister(12))
        pc += current_process.getRegister(arg1);
        
    arg2 = arg2;
}

void CPU::exec_call(int arg1, int arg2)
{
    mem.write(current_process.getRegister(10), pc + 1);
    current_process.setRegister(10, current_process.getRegister(10) - 1);

    pc += current_process.getRegister(arg1);

    arg2 = arg2;
}

void CPU::exec_callm(int arg1, int arg2)
{
    mem.write(current_process.getRegister(10), pc + 1);
    current_process.setRegister(10, current_process.getRegister(10) - 1);

    pc += mem.read(current_process.getRegister(arg1));

    arg2 = arg2;
}

void CPU::exec_ret(int arg1, int arg2)
{
    pc = mem.read(current_process.getRegister(10));
    mem.write(current_process.getRegister(10), -1);

    current_process.setRegister(10, current_process.getRegister(10) + 1);

    arg1 = arg1;
    arg2 = arg2;
}

void CPU::exec_alloc(int arg1, int arg2)
{
    int memSize = current_process.getRegister((arg1));

    int address = mem.allocateMemoryToProcess(current_process.getProcessID(), memSize);
    
    current_process.setRegister(arg2, address);
    pc++;
}

void CPU::exec_acquirelock(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_releaselock(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_sleep(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_setpriority(int arg1, int arg2)
{
    current_process.setPriority(current_process.getRegister(arg1));
    arg2 = arg2;
    pc++;
}

void CPU::exec_exit(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;

    halt = true;
}

void CPU::exec_freememory(int arg1, int arg2)
{
    mem.write(current_process.getRegister(arg1), current_process.getPhysicalAddress(arg2));

    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_mapsharedmem(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_signalevent(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_waitevent(int arg1, int arg2) 
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_input(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_memoryclear(int arg1, int arg2)
{
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_terminateprocess(int arg1, int arg2)
{
    halt = true;
    arg1 = arg1;
    arg2 = arg2;
    pc++;
}

void CPU::exec_popr(int arg1, int arg2)
{
    current_process.setRegister(arg1, mem.read(current_process.getRegister(10)));
    current_process.setRegister(10, current_process.getRegister(10) + 1);
    arg2 = arg2;
    pc++;
}

void CPU::exec_popm(int arg1, int arg2)
{
    mem.write(current_process.getRegister(arg1), mem.read(current_process.getRegister(10)));
    current_process.setRegister(10, current_process.getRegister(10) + 1);
    arg2 = arg2;
    pc++;
}