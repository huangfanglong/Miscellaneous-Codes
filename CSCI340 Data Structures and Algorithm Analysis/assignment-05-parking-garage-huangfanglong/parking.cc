/*
 * Long F. Huang (Z1942308)
 * Assignment 05
 * 10/09/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/

#include "garage.h"
#include <fstream>

void get_input_vals(const std::string &line, char &xact_type, std::string &license);

int main()
{
	//Declaring garage object as 'cgarage'
		garage cgarage;
		
	std::ifstream infile("parking.in");
	std::string line, licenseplate;
	char act;
	
	while(infile.good())
	{ 
		//use getline to read words + whitespace into line
		getline(infile, line);
		get_input_vals(line, act, licenseplate);
			
		if (act == 'A')
		{
			cgarage.arrival(licenseplate);
		}
			
		if (act == 'D')
		{
			cgarage.departure(licenseplate);
		}
		
		//if neither Arrival or Departure, invalid and do nothing
		if (act != 'A' && act != 'D')
		{
			std::cout << "'" << act << "' Invalid action!" << std::endl;
			std::cout << std::endl;
		}
		
	}
	
	infile.close();
	
	return 0;
}

void get_input_vals(const std::string &line, char &xact_type, std::string &license)
{
	xact_type = line.front();
	license = line.substr(2, line.length()-3);
}
		
