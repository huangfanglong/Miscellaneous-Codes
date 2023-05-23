/*
 * Spring 2023 CSCI 350 - PE1
 * Group 4 - Andrew Lee, John Granell, Long Huang, Mert Dogan
 * UDP program: UDP port scanning via timeout
 */
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <chrono>
#include <openssl/rc4.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
	// Create UDP socket
	int sock, rc;
	unsigned int addrlen;
	unsigned char buffer[2048];
	
	// Create the socket
	// Using SOCK_DGRAM parameter to create a UDP socket
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Failed to create socket");
		exit(1);
	}
	
	// Construct the target sockaddr structure
	struct sockaddr_in target;							// Structure for address of the target;
	memset(&target, 0, sizeof(target));					// Clear the struct;
	target.sin_family = AF_INET;						// Internet/IP;
	target.sin_addr.s_addr = inet_addr("10.158.56.43");	// IP address of blitz.cs.niu.edu (NIU local IP address);
	
	// Set socket to time out mode
	struct timeval read_timeout;
	read_timeout.tv_sec = 0;							// Seconds
	read_timeout.tv_usec = 200000;						// Microseconds, varies depending on network connectivity;
	// Set RCVTIMEO(Receive Timeout) to read_timeout
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
	
	// Store the secret key of 16 bytes long for RC4 decryption
	RC4_KEY rc4key;
	
	cout << "Finding an open UDP port:" << endl;
		
	// Loop to probe for response
	for(int port = 9000; port <= 9100; port++)
	{
		target.sin_port = htons(port);					// Target port
		
		// Get time of connection
        auto start_time = chrono::system_clock::now();
		
		// Send packet to target
		rc = sendto(sock, "group 4", 7, 0, (struct sockaddr *) &target, sizeof(target));
		if(rc < 0)
		{
			perror("Error sending packet to target");
			exit(1);
		}
		
		// Receive message back from server
		addrlen = sizeof(target);
		rc = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &target, &addrlen);
		if(rc < 0)
		{
			if(errno == EWOULDBLOCK)
			{
				cout << "." << flush;
				continue;
			}
			
			else
			{
				perror("Error receiving message back from server");
				exit(1);
			}
		}
		
		auto end_time = chrono::system_clock::now();
        	chrono::duration<double> elapsed_seconds = end_time - start_time;
        	time_t end_time_t = chrono::system_clock::to_time_t(end_time);
        	tm *local_end_time = localtime(&end_time_t);
		
		// Set the key retrieved from the response buffer to RC4	
		RC4_set_key(&rc4key, 16, buffer);
		
		cout << "\nTarget port " << ntohs(target.sin_port) << " sent: " << rc << " bytes.\n";
		cout << "Time of connection: " << asctime(local_end_time);
		break;
	}
	
	close(sock);
	
	// Create the TCP socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&target, 0, sizeof(target)); /* Clear struct */
	target.sin_family = AF_INET;			/* Internet/IP */
	target.sin_addr.s_addr = inet_addr("10.158.56.43"); /* IP address */
	
	cout << "Finding an open TCP port:" << endl;
	
	// loop to probe for responses
	for (int port=9000; port <= 9100; port++) {			
		target.sin_port = htons(port); /* target port */	
		
		// Get time of connection
        auto start_time = chrono::system_clock::now();

		// Connect to target
		rc = connect(sock, (struct sockaddr *) &target, sizeof(target));
		if (rc < 0) {
			if (errno == ECONNREFUSED) {
				cout << "." << flush;
				continue;
			} 
			
			else 
			{
				perror("connect");
				exit(EXIT_FAILURE);
			}
		}

		// Send the message to the server 
		if (write(sock, "group 4", 7) < 0) {
			perror("write");
			exit(EXIT_FAILURE);
		}
		// Receive the message back from the server 
		rc = read(sock, buffer, sizeof(buffer));
		if (rc < 0) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		
		auto end_time = chrono::system_clock::now();
        	chrono::duration<double> elapsed_seconds = end_time - start_time;
        	time_t end_time_t = chrono::system_clock::to_time_t(end_time);
        	tm *local_end_time = localtime(&end_time_t);
        
		cout << "\nTarget port " << ntohs(target.sin_port) << " sent: " << rc << " bytes\n";
		cout << "Time of connection: " << asctime(local_end_time);
		break;
	}
	close(sock);
	
	unsigned char *result = new unsigned char[2048];
	
	// Decrypt the received message using RC4 and the secret key
	RC4(&rc4key, rc, buffer, result);
	
	// Add null-terminator to result buffer
	result[rc] = '\0';
	
        cout << "The decrypted message is: \n" << result << endl;
	
	delete[] result;
	return 0;
}