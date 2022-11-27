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

#ifndef HEX_H
#define HEX_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

class hex
{
public :
/**
 * This function return a std::string with exactly 2 hex digits representing the 8 bits ofthe i argument. 
 * */
	static std :: string to_hex8 ( uint8_t i );
/**
 * This function return a std::string with exactly 8 hex digits representing the 32 bits ofthe i argument. 
 * */
	static std :: string to_hex32 ( uint32_t i );
/**
 * This function returns the 32bit hex value as a string with '0x' in front 
 * */
	static std :: string to_hex0x32 ( uint32_t i );
};
#endif
