#include "mainUtilities.h"
#include <iostream>

int main(int argc, char *argv[])
{
	if(argc != 2){
		std::cerr << "Please give a file as an argument" << std::endl;
		exit(-1);
	}

	Graph graph = readGraphFromFile(argv[1]);
	auto net = createResidualNetwork(graph);
	std::cout << "Largest amount of flow possible in this network: " << minCostFlow(net) << std::endl;

	copyNonResidualNetworkEdges(graph,net);

	for(auto v : graph){
		v.printEdges();
	}

	return 0;
}
