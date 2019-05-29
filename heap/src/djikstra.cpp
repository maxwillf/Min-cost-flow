// will use vector < vector<Arc> > adj
// every arc in adj[0] will be the arcs that start on 0
#include <vector>
#include "heap.cpp"
#include <utility>
#include <iostream>

#define LIMIT 2147483647

class Arc{

	public:
	// label of the vertex on which this arc ends
	int dest;
	// weight of the arc
	int weight;

	Arc(int dest, int weight){
		this->dest = dest;
		this->weight = weight;
	}
};

class Vertex
{
	public:
	// number of the vertex
	int label;
	// list of arcs which begin on this vertex
	std::vector<Arc> arcs;

	Vertex(){}

	Vertex(int label){
		this->label = label;
	}
	
	Vertex(int label,std::vector<Arc> arcs){
		this->label = label;
		this->arcs = arcs;
	}

	void addArc(Arc arc){
		arcs.push_back(arc);
	}
};

// injecting specialization of std::hash into namespace std so that we can use
// it with the hashtable that is under the heap
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


// todo change type signature
std::pair<std::vector<int>,std::vector<int>> djikstra(std::vector<Vertex> adj,int source){
	
	std::vector<int> dist(adj.size());
	std::vector<int> prev(adj.size());

	// distance between vertices and the source
	dist[source] = 0;
	// initializing priority queue
	Heap<int,Vertex> queue;
	queue.push(source,adj[source]);
	
	for (int i = 1; i < adj.size(); ++i) {
		dist[i] = LIMIT;	
		queue.push(LIMIT,adj[i]);
	}


	while( !queue.isEmpty() ){
		auto vertex = queue.pop();
		
		for( Arc arc : vertex.arcs ) {
			
			int alt = dist[vertex.label] + arc.weight;
			// checks if alternative path is the	
			if (alt < dist[arc.dest]){
					
				dist[arc.dest] = alt;	
				prev[arc.dest] = vertex.label;
				queue.adjustPriority(alt,adj[arc.dest]);

			}
		}
	}

	return std::make_pair(dist,prev);
}

int main(void){

	std::vector<Vertex> graph;
	graph.push_back(Vertex(0));
	graph.push_back(Vertex(1));
	graph.push_back(Vertex(2));
	graph.push_back(Vertex(3));

	graph[0].addArc(Arc(1,2));
	graph[0].addArc(Arc(2,5));
	graph[1].addArc(Arc(2,1));
	graph[1].addArc(Arc(3,6));
	graph[2].addArc(Arc(3,1));

	auto result = djikstra(graph,0);

	std::cout << "distances to source" <<  std::endl;	
	for( int i : std::get<0>(result) ){

		std::cout << i << std::endl;	
	}

	std::cout << "path from sink to source" <<  std::endl;	
	std::cout << std::get<1>(result)[3] << std::endl;	
	std::cout << std::get<1>(result)[2] << std::endl;	
	std::cout << std::get<1>(result)[1] << std::endl;	
}
