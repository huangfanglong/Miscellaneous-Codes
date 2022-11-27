#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
	//Check for input error--------
	if (argc < 2)
	{
		cerr << "Usage: z1942308 [-c] out_file message_string \n";
		cerr << "where the message_string is appended to file out_file.\n";
		cerr << "The -c option clears the file before the message is appended\n";
		return -1;
	}
	//-----------------------------
	
	char* file = argv[1];
	char* message = argv[2];
	int check = 0;
	int fd;
	//Check if there is a -c command in first parameter after input name
	if (strcmp("-c", argv[1]) == 0)
	{
		check = O_TRUNC;
		file = argv[2];
		message = argv[3];
	}
	
	//Check to see if the output file exists. If it doesn't, create it. 
	//The newly created file is closed at the end of this step.
	int check2 = access(file, F_OK);
	if (check2 == -1)
	{
		fd = open(file, O_WRONLY | O_CREAT, 00000);
		if (fd == -1)
		{
			perror(file);
			exit(EXIT_FAILURE);
		}
		close(check2);
	}
	
	//Check the permissions of the output file. 
	//If any permissions exist, print a useful error message and exit.
	struct stat perm;
	//Guard for error
	if (stat(file, &perm) == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	if ((perm.st_mode & 777) != 0)
	{
		cout << file << " is not secure. Ignoring.\n";
		return 1;
	}
	
	//Change the permissions on the file to allow writing by the user.
	chmod(file, 0200);
	
	//Open the file for output. If the "-c" command line option is present
	//make sure the file is truncated.
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT | check);
	if (fd == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}

	//Write the message from the command line to the output file. 
	write(fd, message, strlen(message));
	//Write an additional newline character so that the output has a nicer format
	write(fd, "\n", 1);
	//Clear the permissions and close the file.
	chmod(file, 0000);
	close(fd);
	
	return 0;
}
