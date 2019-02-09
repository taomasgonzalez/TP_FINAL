#include "DijkstraMachine.h"
#define INF INT_MAX //Infinity
#include <limits.h> 

bool is_floor(const char place);

MapDijkstraMachine::MapDijkstraMachine(unsigned int n_rows, unsigned int n_cols, const char* map_string)
{
	rows = n_rows;
	cols = n_cols;
	
	n_vertices =  rows * cols;

	dist = new int[n_vertices];
	sptSet = new bool[n_vertices];
	parent = new int[n_vertices];
	
	graph = new int*[n_vertices];
	for (int i = 0; i < n_vertices; ++i)
		graph[i] = new int[n_vertices];

	for (int i = 0; i < n_vertices; i++) 
		for (int j = 0; j < n_vertices; j++) {
			graph[i][j] = 0;
		}

	build_graph(map_string);

}


MapDijkstraMachine::~MapDijkstraMachine()
{
	for (int i = 0; i < rows; ++i)
		delete[] graph[i];
	delete[] graph;

	delete dist;
	delete sptSet;
	delete parent;
}
/*
//Implementation for Dijkstra's SSSP(Single source shortest path) algorithm
//This is an optimized algorithm running in O(E*log(V))

void MapDijkstraMachine::run_algorithm(int source_x, int source_y, int destination_x, int destination_y, int n) { //Algorithm for SSSP 
	for (int i = 0; i < sz; i++){
		dis[i] = INF;		//Set initial distances to Infinity
		vis[i] = false;
	}
		
	int source = source_x * cols + source_y;
	int destination = destination_x * cols + destination_y;

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
		for (int i = 0; i < a[cv].size(); i++) //Iterating through all adjacent vertices
			if (!vis[a[cv][i].first] && a[cv][i].second + cw < dis[a[cv][i].first])  //If this node is not visited and the current parent node distance+distance from there to this node is shorted than the initial distace set to this node, update it
				pq.push(make_pair(a[cv][i].first, (dis[a[cv][i].first] = a[cv][i].second + cw))); //Set the new distance and add to priority queue
	}

}
*/

// Funtion that implements Dijkstra's 
// single source shortest path 
// algorithm for a graph represented 
// using adjacency matrix representation 
void MapDijkstraMachine::run_algorithm(int source_x, int source_y) {

	int source = source_x * cols + source_y;
	

	// Initialize all distances as  
	// INFINITE and stpSet[] as false 
	for (int i = 0; i < n_vertices; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// Distance of source vertex from itself is always 0 
	dist[source] = 0;

	// Find shortest path for all vertices 
	for (int count = 0; count < n_vertices - 1; count++)
	{
		/* Pick the minimum distance vertex from the set of vertices not yet processed.  
		 u is always equal to src in first iteration.*/ 
		int u = minDistance();

		// Mark the picked vertex as processed 
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex. 
		for (int v = 0; v < n_vertices; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from u to v, and  
			// total weight of path from src to v through u is smaller than current value of dist[v] 
			if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]){
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
	}
}

Position MapDijkstraMachine::get_next_movement_shortest_path(int source_x, int source_y, int destination_x, int destination_y) {
	run_algorithm(source_x, source_y);

	int destination = destination_x * cols + destination_y;
	form_path_to_vertex(destination);
	Position next_movement;

	int solution = shortest_path.front();
	next_movement.fil = solution / cols;
	next_movement.col = solution % cols;
	return next_movement;
}


// A utility function to find the vertex with minimum distance value,
//from the set of vertices not yet included in shortest path tree 
int MapDijkstraMachine::minDistance(){

	// Initialize min value 
	int min = INT_MAX, min_index;

	for (int v = 0; v < n_vertices; v++)
		if (sptSet[v] == false &&
			dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// Function to print shortest 
// path from source to j 
// using parent array 
void MapDijkstraMachine::form_path_to_vertex(int destination){
	while (shortest_path.size() >= 0)
		shortest_path.pop();

	// Base Case : If destination is source 
	if (parent[destination] == -1)
		return;

	form_path_to_vertex(parent[destination]);
	shortest_path.push(destination);
}

void MapDijkstraMachine::build_graph(const char * map_string) {

	for (int i = 0; i < n_vertices; i++) {
		int row = i / cols;
		int col = i % cols;

		if ((col + 1) < cols)
			graph[i][i + 1] = is_floor(map_string[i + 1]) ? 0 : 1;
		if ((col - 1) >= 0)
			graph[i][i - 1] = is_floor(map_string[i-1]) ? 0 : 1;

		if ((row + 1) < rows)
			graph[i][(row + 1)*cols + col] = is_floor(map_string[(row + 1)*cols + col]) ? 0 : 1;

		if ((row - 1) >= 0)
			graph[i][(row - 1)*cols + col] = is_floor(map_string[(row - 1)*cols + col]) ? 0 : 1;
	}
}

bool is_floor(const char place) {
	return (place == 'F');
}