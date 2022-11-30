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
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::istringstream;

/** 
* Usage message output the correct command line use to display.
*
**********************************************************************************************/ 
static void usage() 
{   
	cerr << "  Usage: [-s server-ip] server-port" << endl;
	cerr << "	-server-ip: Specify the server's IPv4 number in dotted-quad format. " << endl;
	cerr << "	-server-port: The server port number to which the client must connect " << endl;
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
* Print the response sent by the server
*
**********************************************************************************************/ 
static int print_reponse(int fd) 
{	
	char buf[1024];
	int rval = 1;
	
	while(rval > 0)
	{
		if((rval = read(fd, buf, sizeof(buf) - 1)) == 1)
		{
			cerr << "read stream message" << endl;
			return -1;
		}
		
		else if (rval > 0)
		{
			cout << buf << endl;
		}
	}
	return 0;
}

/** 
* Client file read input from stdin then send to server for a response
*
**********************************************************************************************/ 
int main(int argc, char **argv)
{
	// Hold command-line parameters user entered
	int opt;
	//int rval = 1;
	char buffer[1024];
	size_t len = 0;
	const char *ip = "127.0.0.1";	// set default IP address
	string convert;
	
	struct sockaddr_in server;
	
	while ((opt = getopt(argc, argv, "s:")) != -1)   
	{  
		switch (opt)
		{
			case 's':
			{
				istringstream iss(optarg);
				iss >> convert;
				ip = convert.c_str();
			}
			break;

			default:
			{
				usage();
			}
			break;

		}   
	}
	
	if (optind >= argc) 
	{
		usage();
	}
	
	/* Create socket */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) 
	{ perror("Failed to create socket"); exit(1); }
	
	/* Connect socket using name specified by command line. */
	server.sin_family = AF_INET;	// IP Version 4
	
	// Check the first input to see if it is dotted-quad format of IPv4
	// Convert the string value argv[1] into IPv4 address and writes into sin_addr field of server socket/struct
	if(inet_pton(AF_INET, ip, &server.sin_addr) <= 0)
	{ cerr << ip << " invalid address format" << endl; exit(2); }
	
	server.sin_port = htons(atoi(argv[optind]));
	
	if(connect(sock, (sockaddr*)&server, sizeof(server)) < 0)
	{ perror("connecting stream socket"); exit(1); }
	
	while((len = read(fileno(stdin), buffer, sizeof(buffer))))
	{
        if(safe_write(sock, buffer, len) < 0)
        { cerr << "writing on stream socket" << endl; }
    }
	
	// "Half close the socket"
	// Tell the server that no more data will be sent.
	// this will cause any subsequent read() calls to return EOF on the
	// server side!
	shutdown(sock, SHUT_WR);
	
	print_reponse(sock);
	
	close(sock);
	
	return 0;
}

