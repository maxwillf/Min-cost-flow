#include <vector>
#include <iostream>


class Arc{

	public:
	// label of the vertex on which this arc ends
	int dest;
	// distance/weight of the edge
	int weight;
	// upperBound of the arc. Maximum amount of flow that can go through the arc
	int upperBound;
	// current amount of flow going through the arc
	int currentFlow;

	Arc(int dest, int weight, int upperBound){
		this->dest = dest;
		this->weight = weight;
		this->upperBound = upperBound;
		currentFlow = 0;
	}

	int residualCapacity() const{
		return upperBound - currentFlow;
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

	// returns the amount of flow that can be passed through an edge
	int residualCapacity(int v) const{
		// searches arc from this source vertex to vertex v
		for (int i = 0; i < arcs.size(); ++i) {
			if(arcs[i].dest == v){
				return arcs[i].residualCapacity();
			}
		}
		// returns impossible value if there is no such arc
		return -1;
	}

	// adds flow to edge (u,v)
	void addFlow(int v, int flow){

		for (int i = 0; i < arcs.size(); ++i) {
			if(arcs[i].dest == v){
				arcs[i].currentFlow += flow;
			}
		}

		/*for( Arc arc : arcs){
			if(arc.dest == v){
				arc.currentFlow += flow;
			}
		}*/
		return;
	}


	void printEdges(){
		for(Arc arc : arcs){
			std::cout << "Edge from " << label << " to " << arc.dest << " with limit " 
				<< arc.upperBound << " and current flow " << arc.currentFlow << std::endl;
		}
	}
};

typedef std::vector<Vertex> Graph;

