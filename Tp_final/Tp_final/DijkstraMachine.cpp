#include "DijkstraMachine.h"
#define INF INT_MAX //Infinity


MapDijkstraMachine::MapDijkstraMachine(Map * map)
{
	rows = map->get_number_of_rows();
	cols = map->get_number_of_columns();
	
	n_vertices =  rows * cols;
	int curr_weight;

	//Building Graph
	for (int i = 0; i < n_vertices; i++) {
		int row = i / cols;
		int col = i % cols;
		
		if ((col + 1) < cols) {
			curr_weight = map->cell_has_floor(row, col+1) ? INF : 1;
			a[i].push_back(make_pair(row*cols + col+1, curr_weight));
		}
		if ((col - 1) >= 0) {
			curr_weight = map->cell_has_floor(row, col-1) ? INF : 1;
			a[i].push_back(make_pair(row*cols + col-1, curr_weight));
		}
		if ((row + 1) < rows) {
			curr_weight = map->cell_has_floor(row+1, col) ? INF : 1;
			a[i].push_back(make_pair((row+1)*cols + col, curr_weight));
		}
		if ((row - 1) >= 0) {
			curr_weight = map->cell_has_floor(row-1, col) ? INF : 1;
			a[i].push_back(make_pair((row-1)*cols + col, curr_weight));
		}
	}

}


MapDijkstraMachine::~MapDijkstraMachine()
{
}
//Implementation for Dijkstra's SSSP(Single source shortest path) algorithm
//This is an optimized algorithm running in O(E*log(V))

void MapDijkstraMachine::run_algorithm(int source_x, int source_y, int destination_x, int destination_y, int n) { //Algorithm for SSSP 
	for (int i = 0; i < sz; i++){
		dis[i] = INF;		//Set initial distances to Infinity
		vis[i] = false;
	}
		
	int source = source_x * cols + source_y;

	//Custom Comparator for Determining priority for priority queue (shortest edge comes first)
	class prioritize { public: bool operator ()(pair<int, int>&p1, pair<int, int>&p2) { return p1.second>p2.second; } };
	priority_queue<pair<int, int>, vector<pair<int, int> >, prioritize> pq; //Priority queue to store vertex,weight pairs
	pq.push(make_pair(source, dis[source] = 0)); //Pushing the source with distance from itself as 0
	while (!pq.empty())
	{
		pair<int, int> curr = pq.top(); //Current vertex. The shortest distance for this has been found
		pq.pop();
		int cv = curr.first, cw = curr.second; //'cw' the final shortest distance for this vertex
		if (vis[cv]) //If the vertex is already visited, no point in exploring adjacent vertices
			continue;
		vis[cv] = true;
		for (int i = 0; i<a[cv].size(); i++) //Iterating through all adjacent vertices
			if (!vis[a[cv][i].first] && a[cv][i].second + cw<dis[a[cv][i].first]) //If this node is not visited and the current parent node distance+distance from there to this node is shorted than the initial distace set to this node, update it
				pq.push(make_pair(a[cv][i].first, (dis[a[cv][i].first] = a[cv][i].second + cw))); //Set the new distance and add to priority queue
	}

	cout << "Source is: " << source << ". The shortest distance to every other vertex from here is: \n";
	for (int i = 1; i <= n; i++)//Printing final shortest distances from source
	{
		cout << "Vertex: " << i << " , Distance: ";
		dis[i] != INF ? cout << dis[i] << "\n" : cout << "-1\n";
	}
}


