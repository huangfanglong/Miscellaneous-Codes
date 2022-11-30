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
#include <sstream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>

using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::istringstream;
using std::ostringstream;

/** 
* Usage message output the correct command line use to display.
*
**********************************************************************************************/ 
static void usage() 
{    
	cerr << "Usage: server [-l listener-port]" << std::endl;
	cerr << "	-listener-port: The port number to which the server must listen." << endl;
	cerr << "	By default, the port number is zero (wildcard/ephemeral.)" << endl;     
	exit(1); 
} 

/** 
* Same as write() but includes a loop to complete any partials. 
*
**********************************************************************************************/ 
static ssize_t safe_write(int fd, const char *buf, size_t len)
{
	while(len > 0)
	{
		ssize_t wlen = write(fd, buf, len);
		if (wlen == -1)
		{
			return -1;	// write returned an unrecoverable error, errno will be set
		}
		len -= wlen;	// reduce the remaining number of bytes to send
		buf += wlen;	// advance the buffer pointer past the written data
	}
	return len;
}

/** 
* Server file accept connection from client, read and calculate checksum of each byte received
*
**********************************************************************************************/ 
int main(int argc, char **argv)
{
	// Hold command-line parameters user entered
	int opt;
	char buf[1024];
	int rval = 0;
	uint32_t byteCount = 0;
	uint16_t sum = 0;
	uint8_t individualByte = 0;
	uint16_t port = 0;	// set default port to wildcard
	signal(SIGPIPE, SIG_IGN);
	
	// If user has less than 2 inputs, print usage error
	if(argc < 2)
	{ usage(); }
	
	// Process inputs
	while((opt = getopt(argc, argv, "l:")) != -1) 
	{
		switch (opt)
		{
			case 'l':
			{
				istringstream iss(optarg);
				iss >> port;
			}
			break;

			default:
			{
				usage();
			}
			break;
		}
	}
	
	// Create the TCP socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) { perror("opening stream socket"); exit(1); }
	
	// Create address structures
	struct sockaddr_in server_address; // Struct for address of server
	struct sockaddr_in client_address; // Struct for address of client
	
	socklen_t serverAddrLength = sizeof(server_address);
	socklen_t clientAddrLength = sizeof(client_address);
	
	// Construct the server sockaddr_in structure
	memset(&server_address, 0, sizeof(server_address)); // Clear struct
	server_address.sin_family = AF_INET;				// Internet/IP
	server_address.sin_addr.s_addr = INADDR_ANY;		// Any IP address
	server_address.sin_port = htons(port);     	    	// Server port
	
	/* 2 lines below are for references of other applications for .sin_port field */
	//server_address.sin_port = 0;						// Any port
	//server_address.sin_port = htons(9965);			// Server port 9965, this is how servers are commonly setup
	
	// Bind the socket
	if(bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
	{ perror("bind");	exit(1); }
	
	/* Find out assigned port number and print it out */	
	if(getsockname(sock, (sockaddr*)&server_address, &serverAddrLength))
	{ perror("getting socket name"); exit(1); }
	
	cout << "Socket has port #" << ntohs(server_address.sin_port) << endl;
	
	/* Start accepting connections */
	if(listen(sock, 5) < 0) { perror("listen"); exit(1); }
	do
	{
		// Zeroes them out to get rid of garbage
		byteCount = 0;
		sum = 0;
		
		int connSock = accept(sock, (struct sockaddr *) &client_address, &clientAddrLength);
		if (connSock < 0) { perror("accept"); exit(1); }
		
		inet_ntop(client_address.sin_family, &client_address.sin_addr, buf, sizeof(buf));
		cout << "Accepted connection from " << buf << ", port " << ntohs(client_address.sin_port) << endl;
		
		do
		{
			/* Zeroes out all 1024 bytes */
			//bzero(buf, sizeof(buf));
			
			size_t len = sizeof(buf) - 1;
			rval = read(connSock, buf, len);							
			
			if(rval == 0)
			{ cout << "Ending connection\n"; }
			else
			{
				for(int i = 0; i < rval; i++)
				{
					individualByte = buf[i];
					sum += individualByte;
				}
				
				byteCount += rval;
				
				/* Here */
				// Put null pointer at end <- this replaces bzero 
				// on line 152
				buf[rval] = '\0';
			}
		} while (rval != 0);
		
		ostringstream sumlen;
		
		sumlen << "Sum: " << sum << " Len: " << byteCount;
		string str = sumlen.str();
		const char *ch = str.c_str();
		
		safe_write(connSock, ch, strlen(ch));
		
		sleep(1);	
		close(connSock);
			
	} while (true);
	
	/*
	 * Since this program has an infinite loop, the socket "sock" is
	 * never explicitly closed. However, all sockets will be closed
	 * automatically when a process is killed or terminates normally.
	 */
	
	return 0;
}
