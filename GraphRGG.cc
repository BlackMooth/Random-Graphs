#include "GraphRGG.hh"
#include <iterator>

double doubleRand(int max) {
    return max * (double(rand()) / (double(RAND_MAX) + 1.0));
}

double	GraphRGG::distancia(int a, int b){
    double x1 = nodes[a].first;
    double y1 = nodes[a].second;
    double x2 = nodes[b].first;
    double y2 = nodes[b].second;
    
    return sqrt((x2 - x1)*(x2 - x1 ) + (y2 - y1)*(y2 - y1));
}

GraphRGG::GraphRGG(int n,int r){
    nodes = vector < pair<double, double> > (n);
    edges = vector< list<int> > (n);
    int max = 100;
    for(int i = 0; i < n; ++i){
        nodes[i].first = doubleRand(max);
        nodes[i].second = doubleRand(max);
    }  
    randomGeometricGraph(r);
}
void GraphRGG::randomGeometricGraph(int r){
    //arestes si estan a menys distancia que r
    for(int i = 0; i < nodes.size(); ++i ){
        for(int j = i + 1; j < nodes.size(); ++j){
            if(distancia(i,j) <= r){
                edges[i].push_back(j);
                edges[j].push_back(i);
            }
        }
    }
}

void GraphRGG::DFS(int node, vector<bool> & visited) {
    visited[node] = true;
    for(list<int>::iterator it = edges[node].begin(); it != edges[node].end(); it++) {
        if(!visited[*it]) DFS(*it, visited);
    }
}

void GraphRGG::DFS_size(int node, vector<bool> & visited, int & size) {
    visited[node] = true;
    for(list<int>::iterator it = edges[node].begin(); it != edges[node].end(); it++) {
        if(!visited[*it]) {
            ++size; 
            DFS_size(*it, visited, size);
        }
    }
}

int GraphRGG::getCCNumber(){
    vector<bool> visited = vector<bool> (nodes.size(), false);
    int cont = 0;
    
    for(int i = 0; i < nodes.size(); ++i) {
        if(!visited[i]) {
            DFS(i, visited);
            ++cont;
        }
    }
    return cont;
}

bool GraphRGG::isConnex() {
    vector<bool> visited = vector<bool> (nodes.size(), false);
    
    visited[0] = true;
    DFS(0, visited);
    
    for(int i = 0; i < nodes.size(); ++i) {
        if(!visited[i]) return false;
    }
    return true;
}

int GraphRGG::biggestCCSize() {
    vector<bool> visited = vector<bool> (nodes.size(), false);
    int max_size = 0;
    
    for(int i = 0; i < nodes.size(); ++i) {
        if(!visited[i]) {
            int size_current_cc = 1;
            DFS_size(i, visited, size_current_cc);
            if (size_current_cc > max_size) max_size = size_current_cc;
        }
    }
    return max_size;
}