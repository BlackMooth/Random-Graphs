#ifndef BINOMIAL_GRAPHS_HH
#define BINOMIAL_GRAPHS_HH

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <list> 
using namespace std; 

class Graph { 
    int V;    // |V| = n 
    list<int> *adj; // List of adjacency representation
    void DFS_Inm_conn_comp(int v,vector<bool>& visited); 
	void DFS_Inm_giant_comp(int v,vector<bool>& visited, int& N); 

	public: 
    Graph(int V);   
    void addEdge(int v, int w); 
	/* Returns 1 whether the graph is connected. 0, otherwise */
	int isConnex();
	/* Returns the number of connected components in the graph */
    int connectedComponents(); 
	/* Returns 1 whether it is a giant connected component. 0, otherwise */
	int giantComponents();
	~Graph();       
}; 

#endif