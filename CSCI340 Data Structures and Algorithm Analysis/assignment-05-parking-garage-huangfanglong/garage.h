#include "parking.h"
#include <deque>
#include <stack>
#include <algorithm>
#include <iterator>

#ifndef GARAGE
#define GARAGE

class garage
{
public:
        garage(size_t limit = 10) : parking_lot_limit(limit) {}

        /// @param license The license of the car that has arrived.                                                           
        void arrival(const std::string &license);

        /// @param license The license of the car that has departed.                                                          
        void departure(const std::string &license);

private:
        int next_car_id = { 1 };
        std::deque<car> parking_lot;
        size_t parking_lot_limit;
};

void garage::arrival(const std::string &license)
{
	//declaring car object vehicle
	car vehicle(next_car_id, license);
	
	//if lot is less than limit, push in vehicle to parking_lot deque
	if (parking_lot.size() < 10)
	{
		std::cout << vehicle << " has arrived." << std::endl << std::endl;;
		parking_lot.push_back(vehicle);
	}
	
	//if not less than limit, says garage is full and do nothing
	else
	{
		std::cout << vehicle << " has arrived." << std::endl;
		std::cout << "\tBut the garage is full!" << std::endl;
		std::cout << std::endl;
	}	
	next_car_id++;
}

void garage::departure(const std::string &license)
{
	//declaring stack container for moved cars
	std::stack<car> moved;
	//bool function to indicate if the car w/ input license plate is found or not
	bool found = false;
	
	//while parking_lot deque is not empty, check and pull frontal vehicles out one by one
	//into stack container 'moved'
	while(!parking_lot.empty())
	{
		car vehicle1 = parking_lot.front();
		
		//if found a matching license, switch bool to true and remove vehicle from deque parking_lot
		//also take note of # of move
		if (vehicle1.get_license() == license)
		{
			found = true;
			std::cout << vehicle1 << " has departed." << std::endl;
			parking_lot.pop_front();
			vehicle1.move();
			
			//if vehicle has moved before, print msg
			if(vehicle1.get_num_moves() == 1)
			{
				std::cout << "\tcar was moved 1 time in the garage." << std::endl;
			}
			
			if(vehicle1.get_num_moves() > 1)
			{
				std::cout << "\tcar was moved " << vehicle1.get_num_moves() << " times in the garage." << std::endl;
			}
			
			std::cout << std::endl;
			
			break;
		}
		
		else
		{
			moved.push(vehicle1);
			parking_lot.pop_front();
		}
	}
	
	//if license not found in parking lot, print not found
	if (!found)
	{
		std::cout << "No car with license plate \"" << license << "\" is in the garage.";
	}
	
	//move car back from stack 'moved' to deque parking_lot until it is empty
	while(!moved.empty())
	{
		car vehiclemoved = moved.top();
		vehiclemoved.move();
		parking_lot.push_front(vehiclemoved);
		moved.pop();
	}
}

#endif
