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

/**
 * prog2.cpp
 * *
 * Read zero or more 32-bit hex values and then print a detailed 
 * description of the floating point value that they represent by 
 * extracting and showing the sign, exponent, and significand from 
 * the 32-bit value
 *  *
 */


#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cmath>
#include <string>
#include <stack>

using std::hex;
using std::dec;
using std::cout;
using std::cin;
using std::endl;
using std::setfill;
using std::setw;
using std::string;

/**
* @brief Convert float to binary
* This function converts the float value to binary representation.
* @param x is the input 32-bit hex digits
* @return returns the float value in binary
* @note only works for 32-bit hex number values.
***************************************/
string convertFloattoBinary(uint32_t x);

/**
* @brief Convert 32bit hex to binary & print
* This function converts the input 32-bit hex into binary form and prints it
* @param x is the input 32-bit hex digits
* @note only works for 32-bit hex number values.
***************************************/
void printBinary(uint32_t x)
{
	uint32_t mask = 0x80000000;
	for(int i = 1; i <= 32; i++)	// Go through the 32-hex digit and convert it to binary using the mask
	{
		cout << (x & mask ? '1':'0');
		mask >>= 1;
		
		if(i % 4 == 0 && i < 32)				// Add space every 4 numbers
		{
			cout << " ";
		}
	}
	cout << endl;
}

/**
* @brief Print sign, exponent, significand, and final value.
* This function is mainly responsible for printing out the sign, exponent,
* significand and the final value printed in binary.
* @param x is the input 32-bit hex digits
* @note only works for 32-bit hex number values.
***************************************/
void printBinFloat(uint32_t x)
{
	bool sign = x & 0x80000000;
	int32_t mask2 = 0x7f800000;
	int32_t exp = x & mask2;
	exp >>= 23;
	exp -= 127;
	uint32_t sig = x & 0x007fffff;		// Zero out sign and exponent bits
	
	cout << setfill('0');
	cout << "0x" << hex << setw(8) << x << " = ";
	printBinary(x);					  // Print binary equivalent of the 32-bit hex
	cout << "sign: " << sign << endl; //(x & 0x80000000 ? '1':'0') << endl;
	cout << " exp: 0x" << hex << setw(8) << exp << " (" << dec << exp << ")" << endl;
	cout << " sig: 0x" << hex <<setw(8) << sig << endl;	
	cout << convertFloattoBinary(x) << endl;
}	

int main()
{
	uint32_t x;

    //if (cin >> hex >> x)    // Check if input is empty
    //{
		//printBinFloat(x);
		while (cin >> hex >> x)	// Read 32-bit hexadecimal values into x
		{
			printBinFloat(x);
		}
    //}
    
    //else
    //{
		
		//return 0;
	//}
	return 0;
}

string convertFloattoBinary(uint32_t x)
{
    bool sign = x >> 31;				// Shift x 31 to the right to get signed bit
    int exponent = (x >> 23) & 0xff;
    uint32_t fraction = x & 0x7fffff;	// Setting the signed bit to +0

    string result;
    result = sign ? '-' : '+';

    if (exponent == 255) 				// If exponent are all ones(1111 in binary)
    {
        if (fraction == 0) 
        {
            result += "inf";
        } 
        
        else 
        {
            result += "-inf";
        }
    } 
    
    else if (exponent == 0) 
    {
        if (fraction == 0) 
        {
            result += "0";
        } 
        
        else 
        {
            result += "0.";
            result.append(125, '0');	// Add zeroes at the end
            int bit = 23; 
            while(bit-- > 0)		// While bit is > 0, decrement and loop
            {
                result += (fraction >> bit) & 1 ? '1' : '0';	// Get the final value and print it in binary
            }
        }
    } 
    
    else 
    {
        fraction = fraction | 0x800000u;  // Account for the implicit 1, turning it explicit
        exponent = exponent - (127 + 23);
        if (exponent <= -24) 
        {
            result += "0.";
            result.append(-exponent - 24, '0');		// Add zeroes at the end
            int bit = 24; 
            while(bit-- > 0)
            {
                result += (fraction >> bit) & 1 ? '1' : '0';
            }
        } 
        
        else if (exponent >= 0) 
        {
            int bit = 24; 
            while(bit-- > 0)
            {
                result += (fraction >> bit) & 1 ? '1' : '0';
            }
            result.append(exponent, '0');			// Add zeroes at the end
            result += '.';
        } 
        
        else 
        {
            int point = 24 + exponent;
            int bit = 24; 
            while(bit-- > 0)
            {
                result += (fraction >> bit) & 1 ? '1' : '0';
                if (--point == 0) 					// Add '.' at the end when it reaches the last num
                {
					result += '.';
				}
            }
        }
        if (result.back() == '.') result += '0';	// Add a 0 at the end after '.' for formatting
    }

    return result;
}
