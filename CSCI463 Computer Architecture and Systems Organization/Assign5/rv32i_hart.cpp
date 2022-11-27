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

#include "hex.h"
#include "rv32i_decode.h"
#include "rv32i_hart.h"
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

/**
 * Simulates the execution of ebreak instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_ebreak(uint32_t insn, std::ostream* pos)
{
	if (pos)
	{
		std::string s = render_ebreak(insn);
		*pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
		*pos << "// HALT" << std::endl;
	}
	halt = true;
	halt_reason = "EBREAK instruction";
}

/**
 * Reset the rv32i object and the registerfile.
 *
 **************************************************************************/
void rv32i_hart::reset()
{
	// Set pc reg to 0
	pc = 0;
	// Reset the register values
    regs.reset();
    // Set the insn_counter to zero
    insn_counter = 0;
    // Set the the halt flag to false.
    halt = false;
    // Set the the halt_reason to "none".
    halt_reason = "none";
}

/**
 * Dumps the entire state of the hart
 *
 * @param hdr string used for printing prefix
 **************************************************************************/
void rv32i_hart::dump(const std::string &hdr) const
{
	regs.dump(hdr);

	// Dump the PC register 
	std::cout << " pc " << hex::to_hex32(pc) << endl;
}

/**
 * The tick() method function is how to tell the simulator to execute an instruction.
 * 
 * @param hdr string used for printing prefix
 **************************************************************************/
void rv32i_hart::tick(const std::string &hdr)
{
	uint32_t insn;

	// If the hart is halted then return immediately without doing anything
	if(halt) 
	{
		return;
	}
	
	else
	{
		// If show_registers is true then dump the state of the hart with the given hdr
		if(show_registers) 
		{
			dump(hdr);
		}
		
		// If the pc register is not a multiple of 4 then set the halt flag to true, the halt_reason to 
		// "PC alignment error", and return without further processing.
		if(pc % 4 != 0)
		{
			halt = true;
			halt_reason = "PC alignment error";
			return;
		}
		
		// Increment the insn_counter variable 
		insn_counter++;
		// Fetch an instruction from the memory at the address in the pc register.
		insn = mem.get32(pc);

		// If show_instructions is true
		if(show_instructions) 
		{
			// Print the hdr, the pc register (in hex), and the 32-bit fetched instruction (in hex).
			cout << hdr << hex::to_hex32(pc) << ": " << hex::to_hex32(insn) << "  ";
			
			// Call exec(insn, &std::cout) to execute the instruction and render the instruction and
			// simulation details.
			exec(insn, &std::cout);	
		}
		
		else 
		{
			// Call exec(insn, nullptr) to execute the instruction without rendering anything
			exec(insn, nullptr);
		}
	}
}

/**
 * Executes the given RV32I instruction  
 *
 * @param insn The instruction to be executed
 * @param pos  Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec(uint32_t insn, std::ostream* pos)
{
	// Variables to extract the needed instruction fields to decode the instruction 
	uint32_t opcode = get_opcode(insn);
	uint32_t funct3 = get_funct3(insn);
	uint32_t funct7 = get_funct7(insn);

	//  Invoke the associated exec_xxx() helper function using switch-logic
	switch(opcode)
	{
		// If an illegal instruction is encountered then call an exec_illegal_insn()
		default:	   exec_illegal_insn(insn, pos); return;

		case opcode_lui:   exec_lui(insn, pos); return;
		case opcode_auipc: exec_auipc(insn, pos); return;
		case opcode_rtype:
			switch(funct3)
			{
				default:  	  exec_illegal_insn(insn, pos); return;
				case funct3_add:
					switch(funct7)
					{
						default:  	  exec_illegal_insn(insn, pos); return;
						case funct7_add:  return exec_add(insn, pos); return;
						case funct7_sub:  return exec_sub(insn, pos); return;
					}
			    case funct3_sll:  exec_sll(insn, pos); return;
				case funct3_slt:  exec_slt(insn, pos); return;
				case funct3_sltu: exec_sltu(insn, pos); return;
				case funct3_xor:  exec_xor(insn, pos); return;
			 	case funct3_srx:
					switch(funct7)
					{
						default:         exec_illegal_insn(insn, pos); return;
						case funct7_srl: exec_srl(insn, pos); return;
						case funct7_sra: exec_sra(insn, pos); return;
					}
				case funct3_or:   exec_or(insn, pos); return;
				case funct3_and:  exec_and(insn, pos); return;
			}
		case opcode_stype:
			switch(funct3)
			{
				default: 	exec_illegal_insn(insn, pos); return;
				case funct3_sb: exec_sb(insn, pos); return;
				case funct3_sh: exec_sh(insn, pos); return;
				case funct3_sw: exec_sw(insn, pos); return;
			}
		case opcode_alu_imm:
			switch(funct3)
			{
				default:          exec_illegal_insn(insn, pos); return;
				case funct3_sll:  exec_slli(insn, pos); return;
				case funct3_add:  exec_addi(insn, pos); return;
				case funct3_slt:  exec_slti(insn, pos); return;
				case funct3_sltu: exec_sltiu(insn, pos); return;
				case funct3_xor:  exec_xori(insn, pos); return;
				case funct3_or:   exec_ori(insn, pos); return;
				case funct3_and:  exec_andi(insn, pos); return;
			  	case funct3_srx:
					switch(funct7)
					{
						default:         exec_illegal_insn(insn, pos); return;
						case funct7_srl: exec_srli(insn, pos); return;
						case funct7_sra: exec_srai(insn, pos); return;
					}					
			}
		case opcode_load_imm:
			switch(funct3)
			{
				default:	 exec_illegal_insn(insn, pos); return;
				case funct3_lb:  exec_lb(insn, pos); return;
				case funct3_lh:  exec_lh(insn, pos); return;
				case funct3_lw:  exec_lw(insn, pos); return;
				case funct3_lbu: exec_lbu(insn, pos); return;
				case funct3_lhu: exec_lhu(insn, pos); return;
			}
		case opcode_btype:
			switch(funct3)
			{
				default:	  exec_illegal_insn(insn, pos); return;
				case funct3_beq:  exec_beq(insn, pos); return;
				case funct3_bne:  exec_bne(insn, pos); return;
				case funct3_blt:  exec_blt(insn, pos); return;
				case funct3_bge:  exec_bge(insn, pos); return;
				case funct3_bltu: exec_bltu(insn, pos); return;
				case funct3_bgeu: exec_bgeu(insn, pos); return;
			}
		case opcode_jal:  exec_jal(insn, pos); return;
		case opcode_jalr: exec_jalr(insn, pos); return;
		case opcode_system:
			switch(insn)
			{
				default:  
					switch(funct3)
					{
						default: 	     exec_illegal_insn(insn, pos); return;
						case funct3_csrrs:   exec_csrrs(insn, pos); return;
					}
				case insn_ebreak: exec_ebreak(insn, pos); return;
			}
	}

					
}

/**
 * Deal with illegal instructions
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_illegal_insn(uint32_t insn, std::ostream* pos)
{
	if(pos) 
		*pos << render_illegal_insn(insn);
	halt = true;
	halt_reason = "Illegal instruction";
}

/**
 * Simulates the execution of a lui instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_lui(uint32_t insn, std::ostream* pos)
{
	// Sets register rd to imm_u
   	uint32_t rd = get_rd(insn);
   	int32_t imm_u = get_imm_u(insn);

	// Rendering of the simulation details.
   	if(pos)
    {
		std::string s = render_lui(insn);
		*pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
		*pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(imm_u) << std::endl;
    }
	regs.set(rd, imm_u);
	pc += 4;   
}

/**
 * Simulates the execution of an auipc instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_auipc(uint32_t insn, std::ostream* pos)
{
	// Sets register rd to imm_u
	uint32_t rd = get_rd(insn);
	int32_t imm_u = get_imm_u(insn);
	int32_t val = imm_u + pc;

	// Rendering of the simulation details.
	if(pos)
	{
		std::string s = render_auipc(insn);
		*pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
		*pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(pc) << " + " << hex::to_hex0x32(imm_u) << " = " << hex::
			to_hex0x32(val) << std::endl;
	}
	regs.set(rd, val);
	pc += 4;
}

/**
 * Simulates the execution of a jal instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_jal(uint32_t insn, std::ostream* pos)
{
	// Sets register rd to the address of the next instruction
	uint32_t rd = get_rd(insn);
	int32_t imm_j = get_imm_j(insn);
	int32_t val = pc + imm_j;

	// Rendering of the simulation details.
	if(pos)
	{
		std::string s = render_jal(pc, insn);
		*pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
		*pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(pc + 4) << ",  pc = " << hex::
			to_hex0x32(pc) << " + " << hex::to_hex0x32(imm_j) << " = " << hex::to_hex0x32(val) << std::endl;
	}
	
	// Sets pc to the new address given by the pc and imm_j value
	regs.set(rd, pc + 4);
	pc = val;
}

/**
 * Simulates the execution of a jalr instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_jalr(uint32_t insn, std::ostream* pos)
{
	// Sets register rd to the address of the next instruction
	uint32_t rd = get_rd(insn);
	int32_t imm_i = get_imm_i(insn);
	uint32_t rs1 = get_rs1(insn);
	int32_t val = (regs.get(rs1) + imm_i) & 0xfffffffe;

	// Rendering of the simulation details.
	if(pos)
	{
		std::string s = render_jalr(insn);
		*pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
		*pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(pc + 4) << ",  pc = (" << hex::to_hex0x32(imm_i) << " + " << hex::
			to_hex0x32(regs.get(rs1)) << ") & 0xfffffffe = " << hex::to_hex0x32(val) << std::endl;
	}
	
	regs.set(rd, pc + 4);
	pc = val;
}

/**
 * Simulates the execution of a beq instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_beq(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t t_addr;

	// Sets t_addr to pc + imm_b if rs1 and rs2 are equal
    if((uint32_t)regs.get(rs1) == (uint32_t)regs.get(rs2))
    {
      	t_addr = pc + imm_b;
    }
    
   	else
    {
        t_addr = pc + 4;
    }

	// Rendering of the simulation details.
    if(pos)
    {
        std::string s = render_btype(pc, insn, "beq");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " == " << hex::to_hex0x32(regs.get(rs2)) << " ? " << hex::
            to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(t_addr) << std::endl;
    }
    pc = t_addr;
}

/**
 * Simulates the execution of a bne instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 ***************************************************************************/
void rv32i_hart::exec_bne(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t t_addr;

	// Sets t_addr to pc and imm_b if rs1 and rs2 are not equal
    if(regs.get(rs1) != regs.get(rs2))
    {
      	t_addr = pc + imm_b;
    }
    
    else
    {
        t_addr = pc + 4;
    }
    
    // Rendering of the simulation details.
    if(pos)
    {
	    std::string s = render_btype(pc, insn, "bne");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
	    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " != " << hex::to_hex0x32(regs.get(rs2)) << " ? " << hex::
            to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(t_addr) << std::endl; 
    }
    pc = t_addr; 
}

/**
 * Simulates the execution of a blt instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_blt(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t t_addr;

	// Sets t_addr to pc and imm_b if rs1 is less than rs2
    if(regs.get(rs1) < regs.get(rs2))
    {
      	t_addr = pc + imm_b;
    }
    
    else
    {
        t_addr = pc + 4;
    }
    
    // Rendering of the simulation details.
    if(pos)
    {
        std::string s = render_btype(pc, insn, "blt");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
	    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " < " << hex::to_hex0x32(regs.get(rs2)) << " ? " << hex::
            to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(t_addr) << std::endl;
    }
    pc = t_addr;  
}

/**
 * Simulates the execution of a bge instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_bge(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t t_addr;

	// Sets t_addr to pc and imm_b if rs1 is greater than or equal to rs2
    if(regs.get(rs1) >= regs.get(rs2))
    {
      	t_addr = pc + imm_b;
    }
    
    else
    {
        t_addr = pc + 4;
    }

	// Rendering of the simulation details.
    if(pos)
    {
        std::string s = render_btype(pc, insn, "bge");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
	    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " >= " << hex::to_hex0x32(regs.get(rs2)) << " ? " << hex::
            to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(t_addr) << std::endl;
    }
    pc = t_addr;
}

/**
 * Simulates the execution of a bltu instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_bltu(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t t_addr;

	// Sets t_addr to pc and imm_b if rs1 is less than rs2
    if((uint32_t)regs.get(rs1) < (uint32_t)regs.get(rs2))
    {
        t_addr = pc + imm_b;
    }
    
    else
    {
        t_addr = pc + 4;
    }
    
    // Rendering of the simulation details.
    if(pos)
    {
        std::string s = render_btype(pc, insn, "bltu");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << hex::to_hex0x32(regs.get(rs2)) << " ? " << hex::
            to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(t_addr) << std::endl;
    }
    pc = t_addr;
}

/**
 * Simulates the execution of a bgeu instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_bgeu(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t t_addr;

	// Sets t_addr to pc and imm_b if rs1 is >= to rs2
    if((uint32_t)regs.get(rs1) >= (uint32_t)regs.get(rs2))
    {
      	t_addr = pc + imm_b;
    }
    
    else
    {
        t_addr = pc + 4;
    }

	// Rendering of the simulation details.
    if(pos)
    {
        std::string s = render_btype(pc, insn, "bgeu");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " >=U " << hex::to_hex0x32(regs.get(rs2)) << " ? " << hex::
            to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(t_addr) << std::endl;
    }
    pc = t_addr;
}

/**
 * Simulates the execution of a lb instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_lb(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t t_addr = regs.get(rs1) + imm_i;
    uint32_t val = mem.get8(t_addr);
    int32_t num = 0x80;

    val = 0xff & (int32_t)val;

    if(num & val)
    {
        val += 0xffffff00;
    }

    if(pos)
    {
        std::string s = render_itype_load(insn, "lb");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = sx(m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::
            to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a lh instruction
 *
 * @param insn The instruction to be executed
 * @param pos Pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_lh(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t t_addr = regs.get(rs1) + imm_i;
    uint32_t val = mem.get16(t_addr);

    val = 0xffff & (int32_t)val;
    int32_t num = 0x8000;

    if(num & val)
    {
        val += 0xffff0000;
    }

    if(pos)
    {
        std::string s = render_itype_load(insn, "lh");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = sx(m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::
		    to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a lw instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_lw(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t t_addr = regs.get(rs1) + imm_i;
    uint32_t val = mem.get32(t_addr);

    if(pos)
    {
        std::string s = render_itype_load(insn, "lw");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = sx(m32(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::
		    to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a lbu instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_lbu(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t t_addr = regs.get(rs1) + imm_i;
    uint32_t val = mem.get8(t_addr) & 0x000000ff;

    if(pos)
    {
        std::string s = render_itype_load(insn, "lbu");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = zx(m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::
		    to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a lhu instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_lhu(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t t_addr = regs.get(rs1) + imm_i;
    uint32_t val = mem.get16(t_addr) & 0x0000ffff;

    if(pos)
    {
        std::string s = render_itype_load(insn, "lhu");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = zx(m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::
		    to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a sb instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sb(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    uint32_t t_addr = regs.get(rs1) + imm_s;
    uint32_t val = regs.get(rs2) & 0x000000ff;

    if(pos)
    {
        std::string s = render_stype(insn, "sb");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << ") = " << hex::
		    to_hex0x32(val) << std::endl;
    }
    mem.set8(t_addr, val);
    pc += 4;
}

/**
 * Simulates the execution of a sh instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sh(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn); 
    uint32_t t_addr = regs.get(rs1) + imm_s;
    uint32_t val = regs.get(rs2) & 0x0000ffff;

    if(pos)
    {
        std::string s = render_stype(insn, "sh");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << ") = " << hex::
		    to_hex0x32(val) << std::endl;
    }
    mem.set16(t_addr, val);
    pc += 4;
}

/**
 * Simulates the execution of a sw instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sw(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    uint32_t t_addr = regs.get(rs1) + imm_s;
    uint32_t val = regs.get(rs2);

    if(pos)
    {
        std::string s = render_stype(insn, "sw");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// m32(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << ") = " << hex::
		    to_hex0x32(val) << std::endl;
    }
    mem.set32(t_addr, val);
    pc += 4;
}

/**
 * Simulates the execution of an addi instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_addi(uint32_t insn, std::ostream* pos)
{
    int32_t rs1 = get_rs1(insn);
    int32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t sum = regs.get(rs1) + imm_i;

    if(pos)
    {
        std::string s = render_itype_alu(insn, "addi", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::
		    to_hex0x32(imm_i) << " = " << hex::to_hex0x32(sum) << std::endl; 
    }
    regs.set(rd, sum);
    pc += 4;
}

/**
 * Simulates the execution of a slti instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_slti(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = (regs.get(rs1) < imm_i) ? 1 : 0;

    if(pos)
    {
	    std::string s = render_itype_alu(insn, "slti", imm_i);
	    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
	    *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " < " << 
            std::dec << imm_i << ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a sltiu instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sltiu(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = ((uint32_t)regs.get(rs1) < (uint32_t)imm_i) ? 1 : 0;

    if(pos)
    {
        std::string s = render_itype_alu(insn, "sltiu", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << 
		    std::dec << imm_i << ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a xori instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_xori(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = regs.get(rs1) ^ imm_i;

    if(pos)
    {
        std::string s = render_itype_alu(insn, "xori", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " ^ " << hex::
		    to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of an ori instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_ori(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = regs.get(rs1) | imm_i;

    if(pos)
    {
       	std::string s = render_itype_alu(insn, "ori", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " | " << hex::
		    to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of an andi instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_andi(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = (regs.get(rs1) & imm_i);

    if(pos)
    {
        std::string s = render_itype_alu(insn, "andi", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " & " << hex::
		    to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a slli instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_slli(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t shift = get_imm_i(insn)%XLEN;

    int32_t val = regs.get(rs1) << shift;

    if(pos)
    {
        std::string s = render_itype_alu(insn, "slli", get_imm_i(insn));
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " << " << 
		    std::dec << shift << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a srli instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_srli(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t shift = get_imm_i(insn)%XLEN;

    int32_t val = (uint32_t)regs.get(rs1) >> shift;

    if(pos)
    {
        std::string s = render_itype_alu(insn, "srli", get_imm_i(insn));
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << 
		std::dec << shift << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a srai instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_srai(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t shift = get_imm_i(insn)%XLEN;

    int32_t val = regs.get(rs1) >> shift;

    if(pos)
    {
        std::string s = render_itype_alu(insn, "srai", (int32_t)get_imm_i(insn)%XLEN);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << 
		    std::dec << shift << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of an add instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_add(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) + regs.get(rs2);

    if(pos)
    {
        std::string s = render_rtype(insn, "add");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::
		    to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4; 
}

/**
 * Simulates the execution of a sub instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sub(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) - regs.get(rs2);

    if(pos)
    {
        std::string s = render_rtype(insn, "sub");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " - " << hex::
		    to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4; 
}

/**
 * Simulates the execution of a sll instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sll(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t shamt = regs.get(rs2) & 0x01f;
    int32_t val = regs.get(rs1) << shamt;

    if(pos)
    {
        std::string s = render_rtype(insn, "sll");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " << " << 
		    std::dec << shamt << " = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a slt instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_slt(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t val = (regs.get(rs1) < regs.get(rs2)) ? 1 : 0;

    if(pos)
    {
        std::string s = render_rtype(insn, "slt");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " < " << hex::
            to_hex0x32(regs.get(rs2)) << ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a sltu instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sltu(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t val = ((uint32_t)regs.get(rs1) < (uint32_t)regs.get(rs2)) ? 1 : 0; 

    if(pos)
    {
        std::string s = render_rtype(insn, "sltu");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << hex::
		    to_hex0x32(regs.get(rs2)) << ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a xor instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_xor(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) ^ regs.get(rs2); 

    if(pos)
    {
        std::string s = render_rtype(insn, "xor");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " ^ " << hex::
		    to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a srl instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_srl(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t shift = regs.get(rs2) & 0x0000001f;
    int32_t val = (uint32_t)regs.get(rs1) >> shift; 

    if(pos)
    {
        std::string s = render_rtype(insn, "srl");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << 
		    std::dec << shift << " = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a sra instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_sra(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t shift = regs.get(rs2) & 0x0000001f;
    int32_t val = regs.get(rs1) >> shift; 

    if(pos)
    {
        std::string s = render_rtype(insn, "sra");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << 
		    std::dec << shift << " = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of an or instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_or(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) | regs.get(rs2); 

    if(pos)
    {
        std::string s = render_rtype(insn, "or");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " | " << hex::
		    to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of and instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_and(uint32_t insn, std::ostream* pos)
{
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) & regs.get(rs2); 

    if(pos)
    {
        std::string s = render_rtype(insn, "and");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " & " << hex::
		    to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Simulates the execution of a csrrs instruction
 *
 * @param insn The instruction to be executed
 * @param pos A pointer to the output stream object
 **************************************************************************/
void rv32i_hart::exec_csrrs(uint32_t insn, std::ostream* pos)
{
	uint32_t rd = get_rd(insn);
	uint32_t rs1 = get_rs1(insn);
	int32_t csr = get_imm_i(insn) & 0x00000fff;

	// Check for illegal CSR instructions
	if(csr != 0xf14 || rs1 != 0)
	{
		halt = true;
		halt_reason = "Illegal CSR in CRSS instruction";
	}
	
	if(pos)
	{
		std::string s = render_csrrx(insn, "csrrs");
		*pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
		*pos << "// " << render_reg(rd) << " = " << std::dec << mhartid << std::endl;
	}

	if(!halt)
	{
		regs.set(rd, mhartid);
		pc += 4;
	}
}
