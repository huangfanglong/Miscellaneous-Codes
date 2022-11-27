/*
 * Long F. Huang (Z1942308)
 * Assignment 10
 * 12/1/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/

#include "graph.h"

using namespace std;

void Graph::Depthfirst(int v) 
{
	//mark node(bool func) as visited
    this->visited.at(v) = true;
    this->Traversal.at(this->cnt) = v;
    ++this->cnt;

	//iterate through adjacient nodes
    for (auto var : this->adj_list.at(v)) 
    {
		if (!visited.at(var)) {
      
        this->edges.push_back(v);
        this->edges.push_back(var);

        Graph::Depthfirst(var); 

        }
    } 
}

Graph::Graph(const char* filename)
{
    ifstream inFile;
    inFile.open(filename);
    inFile >> this->size;       //gets size 
    
    char temp;

	//label vector
    for(int k = 0; k < this->size; ++k) 
    {
        inFile >> temp;             
        this->labels.push_back(temp);
    }

    int hold;
    int count = 0;
    this->adj_list.resize(this->size);
    
    //gets adjacient nodes
    while(!inFile.eof()) 
    {
        inFile >> temp;
            for(int k = 0; k < this->size; ++k) 
            {
				inFile >> hold;   
                if (hold > 0) 
                {
                    this->adj_list.at(count).push_back(k);
                }
            }
        // ++collum
        ++count;
    }
}

// Clear data
Graph::~Graph()
{
    this->labels.clear();
    this->adj_list.clear();
}

int Graph::Getsize() const 
{ 
	return this->size; 
}

void Graph::Traverse() 
{
	//reset all visits to false and empty the set
    this->visited.resize(this->size, false);
    this->Traversal.resize(this->size, 0);
    this->cnt = 0;

    for(int i = 0; i < this->size ; ++i) 
    {
        if(!visited.at(i)) 
        {
            Graph::Depthfirst(i);               
        }
    }

    cout << "-------- traverse of graph -------" << endl;
    
    for (auto var : this->Traversal) 
    {
        cout << this->labels.at(var) << " ";
    }
    
    cout << endl;

    for (int i = 0; i < this->edges.size(); ++i) 
    {
        cout << "(" << this->labels.at(this->edges.at(i)) << ", " << this->labels.at(this->edges.at(i+1)) << ") ";
        ++i;
    }

    cout << endl;

    cout << "-------- end of traverse -------" << endl;
}

void Graph::Print() const 
{
    cout << "number of vertices in the graph: " << this->size << endl;
    cout << endl;
    cout << "-------- graph -------" << endl;

    for(int i = 0; i < this->size ; ++i) 
    {
		cout << this->labels.at(i) << ": ";
			
		for (auto var : this->adj_list.at(i)) 
		{     
			cout << this->labels.at(var) << ", ";          
		}
    cout << endl;
    }

    cout << "-------- end of graph -------" << endl;
    cout << endl; 
}
