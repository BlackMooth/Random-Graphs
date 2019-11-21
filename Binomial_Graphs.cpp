#include "Binomial_Graphs.hh"

Graph::Graph(int V) { 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) { 
    adj[v].push_back(w); 
    adj[w].push_back(v); 
} 

void Graph::DFS_Inm_conn_comp(int node, vector<bool>& visited) { 
/* This inmersion is used for calculating number of connected components in our graphs */

    visited[node] = true; 
    // cout << node << " ";  /* Uncoment the line if you want to print the connected components of G */
  
	/* Aplying DFS here */ 
    for(list<int>::iterator it = adj[node].begin(); it != adj[node].end(); it++) 
        if(!visited[*it]) DFS_Inm_conn_comp(*it, visited); 
} 

int Graph::connectedComponents() { 
    vector<bool> visited = vector<bool> (V, false);
	int cont = 0;

    for (int v = 0; v < V; v++) { 
        if (!visited[v]) { 
            /* We print all reachable vertices from vertex v */
            DFS_Inm_conn_comp(v, visited); 
            // cout << endl; 
			cont++;
        } 
    } 
	return cont;
}

int Graph::isConnex() {
	int comp = connectedComponents();
	if (comp == 1) return 1;
	else return 0;	
}

void Graph::DFS_Inm_giant_comp(int node, vector<bool>& visited, int& N) { 
/* This inmersion is used for detecting existence of giant component in our graphs */

    visited[node] = true; 
	N++;
  
	/* Aplying DFS here */ 
    for(list<int>::iterator it = adj[node].begin(); it != adj[node].end(); it++) 
        if(!visited[*it]) DFS_Inm_giant_comp(*it, visited, N); 
} 

int Graph::giantComponents() { 
    vector<bool> visited = vector<bool> (V, false);

    for (int v = 0; v < V; v++) { 
        if (!visited[v]) { 
			int N = 0;
            /* We print all reachable vertices from vertex v */
            DFS_Inm_giant_comp(v, visited, N); 
            //cout << "	Number of vertexs in component: " << N << endl; 
			if (N > (V/2)) return int(1);  //This means we have found our giant component
        } 
    } 
	return int(0);
}  

Graph::~Graph() {
   delete[] adj;       
}
  
/* Erdos-Renyi networks generator */
void Erdos_Renyi(int vertex, double p, Graph& G) {
    double probability;
        
    if (p > 1 or p < 0) cout << "p must be in [0, 1]" << endl;
 
	else {        
        //Algorithm to calculate the network model
		for (int i = 0; i < vertex; i++) {
			for(int j = vertex-1; j > i; j--) {
				probability = (rand() % 100) / 100.0;
                if (probability < p) G.addEdge(i, j);
			}
		}
	}
}


int main() {
	srand (time(NULL));
	double p;
	int result, exercise;
	int N[3] = {20, 60, 100}; // Different values of n we'll study

	cout << "Choose [1] for counting connected components of our random graphs" << endl;
	cout << "Choose [2] for studying probability of our  graphs being connected" << endl;
	cout << "Choose [3] for studying probability of our graphs having a giant connected component" << endl;
	cin >> exercise;
	if (exercise < 1 or exercise > 3) cout << "Invalid option" << endl;

	
	for (int i = 0; i < 3; i++) {
		
		ofstream file;	
		string name = "Graph_" + to_string(N[i]);
		if (exercise == 1) name += "_conn_comp.csv"; else if (exercise == 2) name += "_connected.csv";
		else name += "_giant_comp.csv";
		file.open(name);
		
		for (p = 0.01; p <= 0.95; p += 0.01) {	// For each n, we'll vary p from 0.01 to 0.95	
				file << p <<"; ";
				for (int k = 0; k < 10; k++) {		// For each G(n, p), we'll generate K = 10 diferrent graphs
					Graph G(N[i]);
					Erdos_Renyi(N[i], p, G);

					if (exercise == 1) {
						result = G.connectedComponents();
						file << result << "; ";
					}
					else if (exercise == 2) {
						result = G.isConnex();
						file << result << "; ";
					}
					else {
						result = G.giantComponents();
						file << result << "; "; 
					} 
				}
				file << endl;
		}
	}
}

