// will use vector < vector<Arc> > adj
// every arc in adj[0] will be the arcs that start on 0

#include "djikstra.h"

// injecting specialization of std::hash into namespace std so that we can use
// it with the hashtable that is inside the heap
namespace std
{
	template<> struct hash<Vertex>
	{
		typedef Vertex argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& s) const noexcept
		{
			// random hash function
			return (s.label * 3) << 1;
		}
	};
	
	template<> struct equal_to<Vertex>
	{
		typedef Vertex first_argument_type;
		typedef Vertex second_argument_type;
		typedef bool result_type;
		result_type operator()(first_argument_type const& s1, second_argument_type const& s2) const noexcept
		{
			// vertices with the same label are actually the same vertex
			return s1.label == s2.label;
		}
	};
}


std::pair<std::vector<int>,std::vector<int>> djikstra(Graph adj,int source){
	
	std::vector<int> dist(adj.size());
	std::vector<int> prev(adj.size());

	// distance between vertices and the source
	dist[source] = 0;
	prev[0] = 0;
	// initializing priority queue
	Heap<int,Vertex> queue;
	queue.push(source,adj[source]);
	
	for (int i = 1; i < adj.size(); ++i) {
		prev[i] = -1;
		dist[i] = LIMIT;	
		queue.push(LIMIT,adj[i]);
	}

	// while the queue isn't empty, extract the next vertex with the least
	// distance to the source
	while( !queue.isEmpty() ){
		auto vertex = queue.pop();
		
		for( Arc arc : vertex.arcs ) {
			
			// since we are concerned with flow, we will only use non-saturated edges
			if( arc.residualCapacity() > 0){	

				int alt = dist[vertex.label] + arc.weight;
				// checks if alternative path is shorter than current path to
				// the vertex and updates it if it is
				if (alt < dist[arc.dest]){

					dist[arc.dest] = alt;	
					prev[arc.dest] = vertex.label;
					queue.adjustPriority(alt,adj[arc.dest]);

				}
			}
		}
	}
	
	// returns the list of smallest distances to the source and the list of
	// previous vertices in the shortest path to the vertex 
	return std::make_pair(dist,prev);
}
/*

// main function just to test if djikstra is working properly
// and most importantly, if the adjust priority function is working
int main(void){

	std::vector<Vertex> graph;
	graph.push_back(Vertex(0));
	graph.push_back(Vertex(1));
	graph.push_back(Vertex(2));
	graph.push_back(Vertex(3));
	graph.push_back(Vertex(4));

	graph[0].addArc(Arc(1,2));
	graph[0].addArc(Arc(2,8));
	graph[1].addArc(Arc(2,1));
	graph[1].addArc(Arc(3,6));
	graph[2].addArc(Arc(3,1));

	auto result = djikstra(graph,0);

	std::cout << "distances to source" <<  std::endl;	
	for( int i : std::get<0>(result) ){

		std::cout << i << std::endl;	
	}

	std::cout << "path from sink to source" <<  std::endl;
	int current_node = std::get<1>(result)[3];
	std::cout << current_node << std::endl;	
	while(current_node != 0){
		current_node = std::get<1>(result)[current_node];
		std::cout << current_node << std::endl;	
	}

	return 0;
}*/
