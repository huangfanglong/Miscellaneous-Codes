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

#ifndef MEM_H
#define MEM_H

#include "hex.h"
/**
* Simulated memory of bytes
**/
class memory
{
public :
/**
* @param s is the number of bytes to create in the simulated memory
* @note it is rounded up to the next multiple of 16
**/
	memory ( uint32_t s );
	~ memory ();

/**
* Checks if an address is valid
* @param addr is the address being checked
**/
	bool check_illegal ( uint32_t addr ) const ;
/**
* Return the (rounded up) number of bytes in the simulated memory
**/
	uint32_t get_size () const ;
/**
* Return the value of the byte from your simulated memory at the given address
* @param addr is the given address
**/
	uint8_t get8 ( uint32_t addr ) const ;
/**
* Combine 2 bytes into little-endian order and create 16 bit return value
* @param addr is the given address
**/
	uint16_t get16 ( uint32_t addr ) const ;
/**
* Combine 2 bytes into little-endian order and create 32 bit return value
* @param addr is the given address
**/
	uint32_t get32 ( uint32_t addr ) const ;
/**
* Call get8() and then return the sign-extended value of the byte as a 32-bit signed integer
* @param addr is the given address
**/
	int32_t get8_sx ( uint32_t addr ) const ;
/**
* Call get16() and then return the sign-extended value of the 16-bit value as a 32-bit signed integer
* @param addr is the given address
**/
	int32_t get16_sx ( uint32_t addr ) const ;
/**
* Call get32() and then return the value as a 32-bit signed integer
* @param addr is the given address
**/
	int32_t get32_sx ( uint32_t addr ) const ;

/**
* Call check_illegal() to verify the addr argument is valid and set the byte at that address to val
*
* @param addr is the given address
* @param val is the value that was at the given address
**/
	void set8 ( uint32_t addr , uint8_t val );
/**
* call set8() twice to store the given val in little-endian order to the simulated memory
*
* @param addr is the given address
* @param val is the value that was at the given address
**/
	void set16 ( uint32_t addr , uint16_t val );
/**
* Call set16() twice to store the given val in little-endian order into the simulated memory 
*
* @param addr is the given address
* @param val is the value that was at the given address
**/
	void set32 ( uint32_t addr , uint32_t val );
	
/**
* Dumps the content with the corresponding ASCII characters
**/
	void dump () const ;
/**
* Open the file named fname in binary mode  and reads into simulated memory
**/
	bool load_file ( const std :: string & fname );

private :
/**
* The simulated memory vector
**/
	std :: vector < uint8_t > mem ;
};
#endif
