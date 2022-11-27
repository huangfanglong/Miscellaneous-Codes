#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

void processClientRequest(int connSock, char* i);

int main(int argc, char *argv[])
{
	//---If user enter more or less than 3 inputs
	if(argc != 3) 
	{ 
		cerr << "Usage: z1942308 port_number path_name\n";
		exit(EXIT_FAILURE);
	}
	
	// change current directory to argv[2]
	if (chdir(argv[2]) < 0) 
	{
		perror("chdir");
		exit(EXIT_FAILURE);
	}
	
	// Create the TCP socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) { perror("socket"); exit(EXIT_FAILURE); }
	
	// Create address structures
	struct sockaddr_in server_address; // Struct for address of server
	struct sockaddr_in client_address; // Struct for address of client
	unsigned int addrlen = sizeof(client_address);
	
	// Construct the server sockaddr_in structure
	memset(&server_address, 0, sizeof(server_address)); // Clear struct
	server_address.sin_family = AF_INET;				// Internet/IP
	server_address.sin_addr.s_addr = INADDR_ANY;		// Any IP address
	server_address.sin_port = htons(atoi(argv[1]));     // Server port
	
	// Bind the socket
	if(bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	// Make socket passive and set length of queue
	if(listen(sock, 64) < 0) { perror("listen"); exit(EXIT_FAILURE); }
	cout << "Listening on port: " << argv[1] << endl;
	
	// Run until cancelled
	while(true)
	{
		int connSock = accept(sock, (struct sockaddr *) &client_address, &addrlen);
		if (connSock < 0) { perror("accept"); exit(EXIT_FAILURE); }
		
		// Fork
		if(fork()) // Parent
		{
			close(connSock);
		} 
		else 	   // Child
		{
			processClientRequest(connSock, argv[2]);
		}
	}
	close(sock);
	
	return 0;
}

void processClientRequest(int connSock, char* i)
{
	int received;
	char buffer[1024];
	char *path = buffer + 3;
	ostringstream os;
	
	// Read from the client
	if((received = read(connSock, buffer, sizeof(buffer))) < 0)
	{ perror("receive"); exit(EXIT_FAILURE); }
	
	//skip leading whitespaces
	for (; *path == ' '; path++)
	{
		*path ='\0';
	}
	
	if(strncmp(buffer, "GET", 3) == 0)
	{
		// Check if it is a directory or a file
		struct stat s;
		
		// Function to recognize relative path
		if ((stat(path, &s) == -1) && path[0] == '/' ) 
		{ 
			os << i << path;  
			string tmp = os.str();
			strcpy(path, tmp.c_str());

		}
		
		if(stat(path,&s) == 0 )
		{
			if(path[0] == '/' && path != strstr(path, ".."))
			{
				path = path + 1;
				//ignore anything after blanks
				if(path[0] == ' ')
				{
					path[0] = '\0';
				}
				
				if(strlen(path) > 0)
				{
					// remove trailing '/'
					path = path - 1;
				}
				
				if(strlen(path) == 0)
				{
					path[0] = '.';
					path[1] = '\0';
				}
			}
			
			else
			{
				write(connSock, "Invalid path, must start with /", 32);
				close(connSock);
				exit(EXIT_FAILURE);
			}
			
			// It is a directory
			if(s.st_mode & S_IFDIR)
			{
				DIR *dirp = opendir(path);
				if (dirp == 0)
				{
					// Tell client they gave the inappropriate input
					// Duplicate socket descriptor into error output
					// Then print it to client's end with perror to
					// Give more in-depth details of the error to user
					close(2);
					dup(connSock);
					perror(path);
					exit(EXIT_SUCCESS);
				}
			
				struct dirent *dirEntry;
				while((dirEntry = readdir(dirp)) != NULL)
				{
					// If statement to hides all files/folders that start with a dot
					// Which are hidden files/folders
					if(dirEntry->d_name[0] != '.')
					{
						strcpy(path, dirEntry->d_name);
						strcat(path, "\n");
						if(write(connSock, path, strlen(path)) < 0)
						{ perror("write"); exit(EXIT_FAILURE); }
					}
				}
				closedir(dirp);
				close(connSock);
				exit(EXIT_SUCCESS);			
			}
			// It is a file
			else if(s.st_mode & S_IFREG)
			{
				int fd = open(path, O_RDONLY);
				if(fd < 0) { perror("open"); exit(EXIT_FAILURE); }
				
				read(fd, path, sizeof(buffer));
				strcat(path, "\n");
				
				if(write(connSock, path, strlen(path)) < 0)
				{ perror("write"); exit(EXIT_FAILURE); }
				close(fd);
				close(connSock);
				exit(EXIT_SUCCESS);
			}
			// Not a file or directory
			else
			{
				cout << "It is neither a file nor directory!" << endl;
				close(connSock);
				exit(EXIT_FAILURE);
			}
		}
	
		else
		{
			// Same explanation as line 111 - 114
			close(2);
			dup(connSock);
			perror("stat");
			exit(EXIT_SUCCESS);
		}
	}
	close(connSock);
	exit(EXIT_SUCCESS);
}
