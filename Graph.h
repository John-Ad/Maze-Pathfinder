#pragma once

#include "Include.h"

#define INF 99999


class Graph					//adjacency list implementation
{
private:
	struct vertex {
		int vert;
		bool closed;
		int distFromSrc;
		int hDist;
		vertex* prev;

		int x;
		int y;
	};
	struct adjVert{
		int vert;
		int weight;
	};

	vector<vertex> vertices;
	vector<vector<adjVert>> adjList;

	void adjVerts(int v, vector<adjVert>& adjEdg);

	vector<int> walls;
	void initWalls();
public:
	Graph(int size, int x[], int y[], int xSz);
	~Graph();

	void populateList(int x);		//x is the width of the grid
	bool shortestPath(int start, int end, vector<pair<int,int>>& p);
	void resetGraph();
	void getWalls(vector<int>&w);
};

