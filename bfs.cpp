#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>

class Arc{
	int source;
	int dest;
	int weight;
};

// use vector<DirectedEdge>
/*
using namespace std;

#define N 6

void addDirectedEdge(vector<Edge> adj[],int source, int destination){

    adj[source].push_back(destination);
}

int maxFlow(int source, int sink){



}

bool isBipartite(vector<Edge> adj[],int v, vector<bool> &visited,vector<bool> &colors){


}


int main(int argc, char *argv[])
{
    std::vector<Edge> adj[N];
    vector<bool> visited(N);
    vector<bool> colors(N);
	
    addDirectedEdge(adj, 0, 1); 
	addDirectedEdge(adj, 1, 2); 
	addDirectedEdge(adj, 2, 3); 
	addDirectedEdge(adj, 3, 4); 
	addDirectedEdge(adj, 4, 5); 
	addDirectedEdge(adj, 5, 0); 
    
    visited[0] = true;
    colors[0] = 0;

    if(isBipartite(adj,0,visited,colors)){

        std::cout << "YES" << std::endl;
    }
    else {
        std::cout << "SHIEET" << std::endl;
    }
    return 0;
}*/
