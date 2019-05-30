#include "heap.cpp"
#include "djikstra.h"
#include <iostream>

//helper function to be used inside the min-cost-flow function 
// it finds the amount of flow that can be sent through the path
// that is to say, the residualCapacity of the edge with the least residual
// capacity in this path
int pathFlow(const Graph& graph, std::vector<int>& prev){
	
	int dest = prev.size()-1;
	int origin = prev[dest];
	
	int flow = LIMIT;

	// the loop ends when origin == dest
	while(dest != 0){
		int currentEdgeCapacity = graph[origin].residualCapacity(dest);

		if(currentEdgeCapacity < flow && currentEdgeCapacity > 0){
			flow = currentEdgeCapacity;
		}

		dest = origin;
		origin = prev[dest]; 
	}

	return flow;
}

// sends flow through all edges on current path
void sendFlow(Graph& graph, std::vector<int>& prev, int flow){
	
	int dest = prev.size()-1;
	int origin = prev[dest];

	while(dest != 0){
		
		graph[origin].addFlow(dest,flow);
		dest = origin;
		origin = prev[dest]; 
	}
}

int minCostFlow(Graph& graph){

	// adjacency matrix for easier edge checkup	when we know the exact indexes
/*	int maxFlow[graph.size()][graph.size()]  = {0};

	for( Vertex vertex : graph ) {

	}*/
	// receives a std::pair with a list of distances from each vertex to the
	// source and a list of previous vertices on the shortest path to the
	// specified vertex. In this case we're only interested in the list of
	// previous vertices
	std::vector<int> prev = std::get<1> (djikstra(graph,0));
	
	int maxFlow = 0;
	int flow = 0;

	// the sink is the vertex on the last index of the array
	int sink = graph.size()-1;

	bool ThereIsPathToSink = (prev[sink] != -1);

	// checks if there is a vertex that becomes before the sink (vertex in the
	// last index) in the shortest
	// paths found, if there isn't then there is no path from source to sink
	while(ThereIsPathToSink){

		flow = pathFlow(graph,prev);
		maxFlow += flow;
		sendFlow(graph,prev,flow);
		prev = std::get<1> (djikstra(graph,0));
		ThereIsPathToSink = (prev[sink] != -1);
	}
	return maxFlow;
}


int main(int argc, char *argv[])
{

	std::vector<Vertex> graph;
	graph.push_back(Vertex(0));
	graph.push_back(Vertex(1));
	graph.push_back(Vertex(2));
	graph.push_back(Vertex(3));

	graph[0].addArc(Arc(1,2));
	graph[0].addArc(Arc(2,8));
	graph[1].addArc(Arc(2,1));
	graph[1].addArc(Arc(3,6));
	graph[2].addArc(Arc(3,1));

	std::cout << minCostFlow(graph) << std::endl;

	return 0;
}
