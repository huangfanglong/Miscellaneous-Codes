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

#include <iostream> 
#include <thread>
#include <mutex>  
#include <unistd.h>
#include <vector>  

//Global variable declarations
constexpr int rows = 1000;		///< the number of rows in the work matrix constexpr 
constexpr int cols = 100;					///< the number of cols in the work matrix  

std::mutex stdout_lock;			///< for serializing access to stdout
  
std::mutex counter_lock;		///< for dynamic balancing only volatile
// More than 1 thread need to use this variable at the same time, therefore it must be volatile 
volatile int counter = rows;	///< for dynamic balancing only  

std::vector<int> tcount;		///< count of rows summed for each thread 
std::vector<uint64_t> sum;		///< the calculated sum from each thread 
 
int work[rows][cols];			///< the matrix to be summed  

/** 
* Usage message output the correct command line use to display 
*
**********************************************************************************************/ 

static void usage() 
{   
	std::cerr << "Usage: reduce [-d] [-t num]" << std::endl;   
	std::cerr << "    -d use dynamic load balancing" << std::endl;   
	std::cerr << "    -t specifies the number of threads to use" << std::endl;   
	exit(1); 
}  
	
/**  
* Uses static load balancing to determine which rows will be processed by each thread  
*  
* @param tid Thread ID  
* @param num_threads Number of threads  
* 
**********************************************************************************************/ 

void sum_static(int tid, int num_threads) 
{   
	// Lock then print the thread ID of the thread that is starting   
	stdout_lock.lock();   
	std::cout << "Thread " << tid << " starting" << std::endl;   
	stdout_lock.unlock();
	    
	int row = 0;		//the row that will be summed through   
	int count = 0;  
	bool finished = false;	//tells us when to stop summing through rows
	      
	while (!finished)   
	{     
		// Calculate the next row to sum then increment the counter     
		row = tid + (num_threads * count);     
		++count;
		      
		// If row is out of bounds, don't sum it and set finished to true    
		if (row >= rows) 
		{ 
			finished = true; 
		}     
		 
		if (!finished)     
		{            
			uint64_t total = 0;
			
			// For every column in the row, add the value to the total       
			for (int i = 0; i < cols; ++i)       
			{         
				total += work[row][i];       
			}        
			
			// Sum of each row that this thread has finished       
			sum[tid] += total;        
			      
			// Count the number of work units that this thread has processed
			++tcount[tid];     
		}
	}    
	stdout_lock.lock();
	// Print thread ID, number of rows processed, and total sum of each row processed   
	std::cout << "Thread " << tid << " ending tcount=" << tcount[tid] << " sum=" << sum[tid] << std::endl;   
	stdout_lock.unlock(); 
}  
	
/**
*  Uses dynamic load balancing to determine which rows will be processed by each thread  
*  
* @param tid Thread ID  
***********************************************************************************************/ 
void sum_dynamic(int tid) 
{   
	// Lock then print the thread ID of the thread that is starting    
	stdout_lock.lock();   
	std::cout << "Thread " << tid << " starting" << std::endl;   
	stdout_lock.unlock();    
	bool finished  = false; 
   
	while (!finished)   
	{     
		int count_copy; // Copy of counter     
		counter_lock.lock();
		     
		{   
			// If Counter > 0 then decrement        
			if (counter > 0) 
			{ 
				--counter; 
			}
			       
			// Else don't process      
			else 
			{ 
				finished = true; 
			}        
			// Grab a copy that we know is consistent w/ finished flag
			count_copy = counter;	     
		}     
		
		counter_lock.unlock();         		
		if (!finished)     
		{       
			// Do work using the value of count_copy to determine what we do       
			(void)count_copy;	// remove compiler wanring 
			
			// For every column in a row, add the value to the total       
			uint64_t total = 0;       
			for (int i = 0; i < cols; ++i)       
			{         
				total += work[count_copy][i];       
			}        
			
			// Count the sum of each row that this thread has finished       
			sum[tid] += total;        
			
			// Count the number of work units that this thread has processed       
			++tcount[tid];     
		}   
	}    
	
	// Print thread ID, number of rows processed, and total sum of each row processed   
	stdout_lock.lock();   
	std::cout << "Thread " << tid << " ending tcount=" << tcount[tid] << " sum=" << sum[tid] << std::endl;   
	stdout_lock.unlock(); 
}  
	
/**  
* Accepts command-line parameters to either use static or dynamic loading, and set the number of threads  
*  
* @param argc Argument count  
* @param argv Argument values  
*  
* @return 0  
***********************************************************************************************/ 
int main(int argc, char **argv) 
{   
	// Hold command-line parameters user entered
	int opt;
	// Number of threads to use. By default, start two threads  
	unsigned int num_threads = 2;
	// Bool for command-line parameter 'd'  
	bool dCase = false;  
	
	// Holds the thread being used
	std::vector<std::thread*> threads;   
	while ((opt = getopt(argc, argv, "dt:")) != -1)   
	{     
		switch (opt)     
		{       
			// Dynamic load balancing       
			case 'd':       
			{         
				dCase = true;       
			}       
			break;       
			
			// Specifies the number of threads to use       
			case 't':       
			{ 	
				// Store the number in a variable         
				num_threads = atoi(optarg);  	
				
				// If the number entered is greater than or equal to the number of threads the system can use
				// DO NOT start more threads than the system has cores! 	
				if (num_threads >= std::thread::hardware_concurrency()) 	
				{           
					// Use the number of threads the system can use           
					num_threads = std::thread::hardware_concurrency(); 	
				}       
			}       
			break;
						
			default:       
			{         
				usage();       
			}     
		}   
	}    
	
	// Seed the random number generator   
	srand(0x1234);
	
	// Initialize the data in the global work matrix using the rand() function from the standard C library   
	for (int i = 0; i < cols; i++)   
	{     
		for (int j = 0; j < rows; j++)     
		{       
			work[j][i] = rand();     
		}   
	}    
	
	// Print the number of cores in the system   
	std::cout << std::thread::hardware_concurrency() << " concurrent threads supported." << std::endl;    
	
	// Resize the global vectors to size of number of threads and initialize to 0   
	tcount.resize(num_threads, 0);   
	sum.resize(num_threads, 0);
	
	// If optarg -d was in command-line parameter, use dynamic load balancing   
	if (dCase)   
	{     
		// Add the threads to the vector and call sum_dynamic     
		for (unsigned int i = 0; i < num_threads; ++i)     
		{       
			threads.push_back(new std::thread(sum_dynamic, i));     
		}   
	}   
	
	// Else use static load
	
	else   
	{     
		// Add the threads to the vector and call sum_static     
		for (unsigned int i = 0; i < num_threads; ++i)      
		{        
			threads.push_back(new std::thread(sum_static, i, num_threads));     
		}   
	}    
	  
	int total_work = 0;   
	
	for (unsigned int i =0; i < num_threads; ++i)   
	{   
		// Join threads
		threads.at(i)->join();
		
		// Then delete thread object out of the heap to prevent memory leak     
		delete threads.at(i);
		
		// Calculate total work that the threads have finished    
		total_work += tcount.at(i);   
	}		
	
	// Gross sum of threads   
	uint64_t gross_sum = 0;   
	
	for (unsigned int i = 0; i < num_threads; ++i)   
	{      
		gross_sum += sum[i];   
	}    
	
	// Print the total_work and gross_sum then exit the program   
	std::cout << "main() exiting, total_work=" << total_work << " gross_sum=" << gross_sum << std::endl;   

return 0; 
}
