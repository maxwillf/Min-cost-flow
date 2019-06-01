#include "heap.cpp"
#include "graph.h"
#include <iostream>
#include <utility>

// will define this as the true limit minus 100000000 so that it doesn't
// overflow when i need it
#define LIMIT 2047483647

std::pair<std::vector<int>,std::vector<int>> djikstra(Graph adj,int source);
