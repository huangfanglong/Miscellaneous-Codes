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

#ifndef HEX_CPP
#define HEX_CPP
#include "hex.h"

using std::string;

/**
* Returns 8bit hex value as a string with exactly 2 hex digits
* @param i 8bit hex value
* @return return a std::string with exactly 2 hex digits representing the 8 bits of the i argument.
**/
string hex::to_hex8(uint8_t i) 
{
	std::ostringstream os;
	os << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(i);

	return os.str();
}

/**
* Returns 32bit hex value as a string with exactly 8 hex digits
* @param i 32bit hex value
* @return return a std::string with exactly 8 hex digits representing the 32 bits of the i argument.
**/
string hex::to_hex32(uint32_t i) 
{
	std::ostringstream os;
	os << std::hex << std::setfill('0') << std::setw(8) << i;

	return os.str();
}

/**
* Returns the 32bit hex value as a string with '0x' in front
* @param i 32bit hex value
* @return 32bit hex value as a string with '0x' in front
**/
string hex::to_hex0x32(uint32_t i) 
{
	return string("0x")+to_hex32(i);
}

#endif

