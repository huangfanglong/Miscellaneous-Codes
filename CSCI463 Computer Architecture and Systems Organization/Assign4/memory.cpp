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

#ifndef MEM_CPP
#define MEM_CPP
#include "hex.h"
#include "memory.h"

/**
* Constructor for memory class
*
* Sets the memory size, rounded up to mod-16
* @param siz Unsigned integer containing the size of memory to allocate
**/
memory::memory(uint32_t siz) 
{
	siz = (siz+15)&0xfffffff0; //round the length up, mod-16

	mem.resize(siz, 0xa5); // allocate and initialize every byte/element in mem vector to 0xa5.
}

/**
* Destructor for memory class
**/
memory::~memory() {}

/**
* Checks if the given address is within the range of valid addresses of the simulated memory
* @param i is the given address
* @return Return true if the given address i does not represent an element that is present in the mem vector
**/
bool memory::check_illegal(uint32_t i) const 
{
	// If the given address is not within the range of valid addresses of the simulated memory
	if(i >= memory::get_size()) 
	{
		std::cout << "WARNING: Address out of range: " << hex::to_hex0x32(i) << std::endl;
		return true;
	}
	
	else 
	{
		return false;
	}
}

/**
* Return the (rounded up) number of bytes in the simulated memory.
* @return Returns the rounded up memory size
**/
uint32_t memory::get_size() const 
{
	return mem.size();
}

/**
* Check to see if the given addr is in your mem and return the value of the byte
* 
* @param addr is the given address
* @return return the value of the byte from your simulated memory at the given address. If addr is not in the valid range then return zero.
**/
uint8_t memory::get8(uint32_t addr) const 
{
	if(!memory::check_illegal(addr)) 
	{
		return mem[addr];
	}
	
	else 
	{
		return 0;
	}
}

/**
* Combine 2 bytes into little-endian order and create 16 bit return value
*
* @param addr is the given address
* @param MSB is the first byte to be combined with the second byte
* @param LSB is the second byte to be combined with the first byte
* 
* @return The combined bytes at the given address
**/
uint16_t memory::get16(uint32_t addr) const 
{
	uint8_t LSB = get8(addr);
	uint8_t MSB = get8(addr + 1);
	return ((uint16_t)MSB << 8) | LSB;
}

/**
* Combine 2 bytes into little-endian order and create 32 bit return value
*
* @param addr is the given address
* @param MSB is the first byte to be combined with the second byte
* @param LSB is the second byte to be combined with the first byte
* 
* @return The combined bytes at the given address
**/
uint32_t memory::get32(uint32_t addr) const 
{
	uint16_t LSB = get16(addr);
	uint16_t MSB = get16(addr + 2);
	return ((uint32_t)MSB << 16) | LSB;
}

/**
* Call get8() and then return the sign-extended value of the byte as a 32-bit signed integer
*
* @param addr is the given address
*
* @return return the sign-extended value of the byte as a 32-bit signed integer
**/
int32_t memory::get8_sx(uint32_t addr) const 
{
	int32_t val = get8(addr);
	return val | (val&0x00000080 ? 0xffffff00 : 0);
}

/**
* Call get16() and then return the sign-extended value of the 16-bit value as a 32-bit signed integer
*
* @param addr is the given address
*
* @return return the sign-extended value of the 16-bit value as a 32-bit signed integer
**/
int32_t memory::get16_sx(uint32_t addr) const 
{
	int32_t val = get16(addr);
	return val | (val&0x00008000 ? 0xffff0000 : 0);
}

/**
* Call get32() and then return the value as a 32-bit signed integer
*
* @param addr is the given address
*
* @return return the value as a 32-bit signed integer
**/
int32_t memory::get32_sx(uint32_t addr) const 
{
	return memory::get32(addr);
}

/**
* Call check_illegal() to verify the addr argument is valid and set the byte at that address to val
*
* @param addr is the given address
* @param val is the value that was at the given address
**/
void memory::set8(uint32_t addr, uint8_t val) 
{
	if (!memory::check_illegal(addr)) 
	{
		mem[addr] = val;
	}
}

/**
* call set8() twice to store the given val in little-endian order to the simulated memory
*
* @param addr is the given address
* @param val is the value that was at the given address
* @param MSB is the first byte to be combined with the second byte
* @param LSB is the second byte to be combined with the first byte
**/
void memory::set16(uint32_t addr, uint16_t val) 
{
	// Get the MSB and shift it right
	uint8_t MSB = (uint8_t)((val & 0xFF00) >> 8);
	// Get LSB
	uint8_t LSB = (uint8_t)(val & 0x00FF);
	// Set it into little-endian order, putting the LSB first and MSB last
	memory::set8(addr, LSB);
	memory::set8(addr + 1, MSB);
}

/**
* Call set16() twice to store the given val in little-endian order into the simulated memory 
*
* @param addr is the given address
* @param val is the value that was at the given address
* @param MSB is the first byte to be combined with the second byte
* @param LSB is the second byte to be combined with the first byte
**/
void memory::set32(uint32_t addr, uint32_t val) 
{
	// Get the MSB and shift it right
	uint16_t MSB = (uint16_t)((val & 0xFFFF0000) >> 16);
	// Get LSB
	uint16_t LSB = (uint16_t)(val & 0x0000FFFF);
	// Set it into little-endian order, putting the LSB first and MSB last
	memory::set16(addr, LSB);
	memory::set16(addr + 2, MSB);
}

/**
* Dumps the content with the corresponding ASCII characters
*
* Dump the entire contents of your simulated memory in hex with the corresponding ASCII
* characters on the right exactly, space-for-space in the format shown in the output section
* of the handout
* @param dot is used to format and store the corresponding number of dots when the byte does not have a valid printable value
**/
void memory::dump() const 
{
	std::string dot = "";
	for (uint32_t addr = 0; addr < get_size() ; ++addr) 
	{
		if (addr % 16 == 0)
		{
			std::cout << std::setfill('0') << std::setw(8) << hex::to_hex32(addr) << ": ";
		}

		std::cout << hex::to_hex8(get8(addr)) << " ";

		uint8_t ch = get8(addr);
		ch = isprint(ch) ? ch : '.';
		dot += ch;	// Store the corresponding number of dots to be printed

		if (addr % 16 == 7)
		{
			std::cout << " ";
		}
		
		if (addr % 16 == 15) 
		{
			std::cout << "*" << dot << "*" << std::endl;
			dot.clear();
		}
	}
}

/**
* Open the file named fname in binary mode  and reads into simulated memory
**/
bool memory::load_file(const std::string &fname) 
{
	std::ifstream infile(fname, std::ios::in|std::ios::binary);

	if (infile.is_open()) 
	{
		uint8_t i;
		infile >> std::noskipws;
		for (uint32_t addr = 0; infile >> i; ++addr) 
		{
			if (memory::check_illegal(addr)) 
			{
				std::cerr << "Program too big." << std::endl;
				return false;
			}
			set8(addr, i);
		}
		return true;
	}
	
	else 
	{
		std::cerr << "Can't open file '" << fname << "' for reading." << std::endl;
		return false;
	}
}
#endif
