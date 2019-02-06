#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include "Map.h"
using namespace std;

class MapDijkstraMachine
{
public:
	MapDijkstraMachine(Map* map);
	~MapDijkstraMachine();

	void run_algorithm(int source_x, int source_y, int destination_x, int destination_y, int n);

private:

	static const int sz = 10001; //Maximum possible number of vertices. Preallocating space for DataStructures accordingly
	vector<pair<int, int> > a[sz]; //Adjacency list
	int dis[sz]; //Stores shortest distance
	bool vis[sz] = { 0 }; //Determines whether the node has been visited or not

	int n_vertices;
	int n_edges;

	int rows; 
	int cols;
};

