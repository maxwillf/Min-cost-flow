#include "djikstra.h"
#include <fstream>
#include <sstream>

void copyNonResidualNetworkEdges(Graph & graph, const Graph & net);

int pathFlow(const Graph& graph, std::vector<int>& prev);

void sendFlow(Graph& graph, std::vector<int>& prev, int flow);

bool ThereIsPathToSink(std::vector<int>& prev);

int minCostFlow(Graph& graph);

Graph createResidualNetwork(const Graph & graph);

Graph readGraphFromFile(char * str);
