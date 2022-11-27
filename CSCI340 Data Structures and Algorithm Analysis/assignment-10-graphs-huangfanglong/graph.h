#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <stack>

class Graph {
 private:
  int size;
  std::vector<std::list<int> > adj_list;
  
  // Chars for the numbers
  std::vector<char> labels;
  
  // Mark for visited nodes
  std::vector<bool> visited;
  
   // Hold the edges of the path
  std::vector<int> edges;
  
  // Positional count
  int cnt;
  
  std::vector<int> Traversal;   
  void Depthfirst(int);

 public:
  Graph(const char* filename);
  ~Graph();
  int  Getsize() const;
  void Traverse();
  void Print() const;
};

#endif  // GRAPH_H

