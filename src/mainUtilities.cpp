#include "mainUtilities.h"

// after the algorithm has finished we need to update the edges of the
// original graph in order to properly print our solution
// the first argument is the original graph and the second one is the
// residual network that was used in the min-cost-flow algorithm
void copyNonResidualNetworkEdges(Graph & graph, const Graph & net){
		for (int i = 0; i < graph.size(); ++i) {
			// modifying the original graph
			for (int j = 0; j < graph[i].arcs.size(); ++j) {
				graph[i].arcs[j] = net[i].arcs[j];
			}
		}
	}

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
		// sendflow using residual nets
		graph[dest].addFlow(origin,flow * -1);
		dest = origin;
		origin = prev[dest]; 
	}
}

// checks if there is a path from the origin to the sink
bool ThereIsPathToSink(std::vector<int>& prev) {

	int dest = prev.size()-1;
	int origin = prev[dest];
	while(dest != 0){
		// if the path abruptly ends 
		if(dest == -1){
			return false;	
		}
		dest = origin;
		origin = prev[dest]; 
	}
	return true;
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

	// checks if there is a vertex that becomes before the sink (vertex in the
	// last index) in the shortest
	// paths found, if there isn't then there is no path from source to sink
	while(ThereIsPathToSink(prev)){

		flow = pathFlow(graph,prev);
		maxFlow += flow;
		sendFlow(graph,prev,flow);
		prev = std::get<1> (djikstra(graph,0));
	}
	return maxFlow;
}

Graph createResidualNetwork(const Graph & graph){

	// copying the original graph
	Graph residualNet;
	for(Vertex v : graph){
		residualNet.push_back(v.label);

		for(Arc arc : v.arcs){
			residualNet[v.label].addArc(Arc(arc.dest,arc.weight,arc.upperBound));
		}
	}

	// adding the symmetrical edges
	
	for(Vertex v : graph){
		for(Arc arc : v.arcs){

			Arc e = Arc(v.label,arc.weight,arc.upperBound);
			e.currentFlow = e.upperBound;
			residualNet[arc.dest].addArc(e);
		}
	}

	return residualNet;
}

Graph readGraphFromFile(char * str){

	Graph graph;

	std::ifstream ifs(str);
	std::string line;
	std::stringstream ss;

	int graphSize;

	// if the file is on proper format defined by the README the first variable is
	// an int containing the graphsize
	getline(ifs,line);
	ss << line;
	ss >> graphSize;

	// initialize graph vertices
	for (int i = 0; i < graphSize; ++i) {
		graph.push_back(Vertex(i));	
	}

	int label,dest,weight,upperBound;

	// add all arcs defined in the txt file 
	while(getline(ifs,line)){
		ss = std::stringstream(line);
		ss >> label >> dest >> weight >> upperBound;

		// exits if given input file has out of bounds indexes
		if(label >= graphSize or dest >= graphSize or label < 0 or dest < 0){
			std::cerr << "Incorrect graph labels used. Indexes are out of bounds. Please use a proper input file" << std::endl;
			exit(-1);
		}

		// exits if edges weights are negative values. the algorithm wouldn't
		// work because djikstra doesn't support negative values
		if( weight < 0){
			std::cerr << "Negative edge's weight used. Djikstra doesn't work properly with this kind of input. Please use edges with non-negative weights only." << std::endl;
		}

		graph[label].addArc(Arc(dest,weight,upperBound));

#ifdef DEBUG
		std::cout <<  label << dest << weight << upperBound <<  std::endl;
#endif
	}
	return graph;
}

