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

#ifndef REG_H
#define REG_H

#include <string>
#include <stdint.h>

class registerfile
{
	public:
		registerfile();
		void reset();
		void set(uint32_t r, int32_t val);
		int32_t get(uint32_t r) const;
		void dump(const std::string &hdr) const;

	private:
		int32_t reg[32];
};

#endif
