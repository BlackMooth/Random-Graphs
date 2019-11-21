#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <list>

using namespace std;
class GraphRGG{		
	private:
		vector< pair<double,double> > nodes;
		vector< list<int> > edges;
	
		void randomGeometricGraph(int r);
		double distancia(int a, int b);
                void DFS(int node, vector<bool> & visited);
                void DFS_size(int node, vector<bool> & visited, int & size);
                
        
        
	public:
		GraphRGG(int n, int r);
                int getCCNumber();
                int biggestCCSize();
                bool isConnex();

};
