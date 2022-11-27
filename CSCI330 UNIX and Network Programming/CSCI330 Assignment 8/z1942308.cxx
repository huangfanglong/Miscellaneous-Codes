#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>

using namespace std;

int main()
{
	int rs, pid, status;
	string file, command, argument,input;
	istringstream iss;
	
	while(command != "exit")
	{
		cin.clear();
		cout << "Enter command: ";
		getline(cin,input);
		iss.clear();
		iss.str(input);
		iss >> command >> argument >> file;
		
		pid = fork();
		if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }
	
		if (pid == 0)
		{
			if (file.length() < 2) 
			{
                rs = execlp(command.c_str(), argument.c_str() , argument.c_str() , (char*) NULL);
            
                if (rs == -1) { perror("execlp"); exit(EXIT_FAILURE); }
            }
            
            else 
            {
                rs = execlp(command.c_str(), argument.c_str() , file.c_str() , (char*) NULL);
                
                if (rs == -1) { perror("execlp"); exit(EXIT_FAILURE); }
            }
		}
	
		else
		{
			wait(&status);
		}
	}
	return 0;
}

