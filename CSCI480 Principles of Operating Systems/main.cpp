/********************************************************
 * CSCI 480 MidOS Project
 * 
 * Julia Finegan
 * Long Huang
 * Brandon Romito
 * David Ostman
 * Gurpreet Girn
**********************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "MMU.h"
#include "CPU.h"
#include "PCB.h"

using namespace std;

MMU loadPrograms(int argCount, char *argVector[]);
vector<string> readInstructionsFromFile(string filename);


int main(int argc, char *argv[])
{
    MMU mem = loadPrograms(argc, argv);
    
    CPU midOS(mem);
    midOS.reset();
    midOS.run();

    return 0;
}

MMU loadPrograms(int argCount, char *argVector[])
{
    if(argCount < 3)
        exit(-1);

    int virtualMemSize = atoi(argVector[1]);
    int numProcesses = argCount - 2;
    char initialState[virtualMemSize] = {-1};

    MMU mem(virtualMemSize, 16, numProcesses);

    for(int i = 2; i < argCount; i++)
    {
        vector<string> instructions = readInstructionsFromFile(argVector[i]);
        string discName = "process" + to_string(i-2) + ".bin";

        ofstream ofs(discName, ios::binary | ios::out);
        if(!ofs.write(initialState, virtualMemSize))
            exit(-1);

        mem.createProcess(virtualMemSize, instructions, discName);
    }
    //cout << "load programs 3" << endl;

    return mem;
}

vector<string> readInstructionsFromFile(string filename)
{
    vector<string> instructions;
    ifstream infile(filename);
    if (!infile) 
    {
        cerr << "Error opening file" << filename << endl;
        exit(1);
    }
    string line;
    while (getline(infile, line)) 
    {
        // Remove comments by finding ';' and erasing everything after it
        size_t comment_pos = line.find(';');
        if (comment_pos != string::npos) 
        {
            line.erase(comment_pos);
        }
        
        // Erase trailing whitespace
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        // Ignore line if it is empty after removing comments and whitespace
        if (line.empty()) 
        {
            continue;
        }
        // Add line to instructions vector
        instructions.push_back(line);
    }
    return instructions;
}