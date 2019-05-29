// will use vector < vector<Arc> > adj
// every arc in adj[0] will be the arcs that start on 0


#define INFINITY 2147483647

class Vertex
{
	// number of the vertex
	int label;
	// list of arcs which begin on this vertex
	vector<Arc> arcs;
}

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

type djikstra(vector<Vertex> adj,int source){
	
	vector<int> dist(adj.size());
	vector<int> prev(adj.size());

	// distance between vertices and the source
	dist[source] = 0;
	for (int i = 1; i < adj.size(); ++i) {
		dist[i] = INF	
	}

	// initializing priority queue
	Heap<int,Vertex> queue;
	queue.push(adj[source],source);

	while( !Q.isEmpty() ){
		auto vertex = queue.pop();
		
		for( Arc arc : vertex.arcs ) {
			
			int alt = dist[vertex] + arc.weight;
			// checks if alternative path is the	
			if (alt < dist[arc.dest]){
					
				// add the vertex in the queue if it isn't yet
				if(dist[arc.dest] == INFINITY){
					queue.push(alt,arc.dest);
				}
				// 
				dist[arc.dest] = alt;	
				prev[arc.dest] = vertex.label;

			}
		}
	}
}
