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

#include "registerfile.h"
#include "hex.h"
#include <cstdint>
#include <iostream>
#include <iomanip>

using std::cout;

/**
 * Constructor that uses the reset() method to initialize register x0 to zero
 * 
 **************************************************************************/
registerfile::registerfile()
{
	reset();
}

/**
 * Initialize register x0 to zero, and all other registers to 0xf0f0f0f0.
 * 
 **************************************************************************/
void registerfile::reset()
{
	reg[0] = 0x0;

	for (int i = 1; i < 32; i++)
	{
		reg[i] = 0xf0f0f0f0;
	}
}

/**
 * Assign register r the given val. If r is zero then do nothing.
 * 
 * @param r Register
 * @param val Given value
 * 
 **************************************************************************/
void registerfile::set(uint32_t r, int32_t val)
{
	if (r == 0)
	{
		return;
	}
	else
	{
		reg[r] = val;
	}
}

/**
 * Return the value of register r. If r is zero then return zero
 * 
 * @param r Register
 * 
 * @return 0 or value of register r
 * 
 **************************************************************************/
int32_t registerfile::get(uint32_t r) const
{
	if (r == 0)
	{
		return 0;
	}
	else
	{
		return reg[r];
	}
}

/**
 * Dump the registers
 * 
 * @param hdr string used for printing prefix
 * 
 **************************************************************************/
void registerfile::dump(const std::string &hdr) const
{
	for(size_t i = 0; i < 32; i++)
	{
		// New line every 8
		if (i != 0 && i % 8 == 0)
		{
			cout << std::endl;
		}
		
		if (i % 8 == 0)
		{
			std::string h;
			if (i == 0)
			{
				h = "x0";
			}
			
			else if (i == 8)
			{
			    h = "x8";
            }
            
            else if(i == 16)
            {
                h = "x16";
            }
            
            else if(i == 24)
            {
                h = "x24";
            }
			cout << hdr << std::dec << std::right << std::setw(3) << std::setfill(' ') << h << " ";
        }

        // Print register contents
        if(i % 8 == 7)
        {
            cout << hex::to_hex32(reg[i]);
        }
        
		else if(i % 4 == 0 && i != 0 && i % 8 != 0)
		{
			cout << " " << hex::to_hex32(reg[i]) << " ";
		}
		
		else
		{
            cout << hex::to_hex32(reg[i]) << " ";
        }
    }
	cout << std::endl;
}

