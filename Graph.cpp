#include "Graph.h"



Graph::Graph(int size, int x[], int y[], int xSz)
{
	vertex v;
	v.distFromSrc = INF;
	v.hDist = INF;
	v.closed = false;
	v.prev = NULL;

	int xCount = 0;
	int yCount = 0;

	for (int i = 0; i < size; i++)
	{
		if (xCount == xSz)
		{
			xCount = 0;
			yCount++;
		}
		v.x = x[xCount];
		v.y = y[yCount];

		v.vert = i;
		vertices.push_back(v);

		xCount++;
	}

	//ohter init functions
	initWalls();
}
Graph::~Graph()
{
}

void Graph::initWalls()
{
	srand(time(NULL));

	int randNum = 0;
	for (int i = 0; i < vertices.size() / 2; i++)
	{
		randNum = rand() % (vertices.size() - 1) + 1;
		vertices[randNum].closed = true;
		walls.push_back(randNum);
	}
}

void Graph::populateList(int x)
{
	int xHolder{ x - 1 };
	adjVert v;

	for (int i = 0; i < vertices.size(); i++)
	{
		adjList.push_back(vector<adjVert>());
	}

	for (int i = 0; i < adjList.size(); i++)			// refer to a drawn grid when working through this algorithm
	{
		for (int e = 0; e < adjList.size(); e++)
		{
			if (e == i + 1 && i != xHolder)		// links a vertex to the one to the right of it
			{
				v.vert = vertices[e].vert;
				v.weight = 1;

				adjList[i].push_back(v);
			}
			else if (e == i - 1 && e != xHolder)	// links a vertex to the one to the left of it
			{
				v.vert = vertices[e].vert;
				v.weight = 1;
				adjList[i].push_back(v);
			}
			else if (e == i + x)				//links a vertex to the one under it
			{
				v.vert = vertices[e].vert;
				v.weight = 1;
				adjList[i].push_back(v);
			}
			else if (e == i - x)				//links a vertext to the one above it
			{
				v.vert = vertices[e].vert;
				v.weight = 1;
				adjList[i].push_back(v);
			}
			
			if (e == xHolder + 1)					//xholder signals the end of a row. Doubling it moves the algorithm to the next row
			{
				xHolder += x;
			}
		}
		xHolder = x - 1;
	}
}
void Graph::adjVerts(int v, vector<adjVert>& adjVert)
{
	if (adjVert.size() > 0)		//function automatically clears the vector passed in if necessary
		adjVert.clear();

	for (int i = 0; i < adjList[v].size(); i++)
	{
		adjVert.push_back(adjList[v][i]);
	}
}

bool Graph::shortestPath(int start, int end, vector<pair<int, int>>& p)
{
	bool pathFound = false;			//controls main loop
	int currentVert = start;		//represents current vertex
	int vertToDel = INF;			//used to erase current vert from open list
	int shortestDist = INF;			//helps choose the next vertex to visit
	int hX = 0;						//heuristic x and y variables
	int hY = 0;

	bool inOpen = false;

	vector<int> open;		//open vertices
	vector<vertex> path;		//used to display path
	vector<adjVert> adjVert;		//used to store adjacent vertices

	currentVert = start;
	vertices[currentVert].distFromSrc = 0;
	vertices[currentVert].hDist = 0;
	open.push_back(vertices[currentVert].vert);

	do
	{
		for (int i = 0; i < open.size(); i++)
		{
			if (vertices[open[i]].hDist < shortestDist)
			{
				shortestDist = vertices[open[i]].hDist;
				currentVert = vertices[open[i]].vert;
				vertToDel = i;
			}
		}
		if (open.size() != 0)
		{
			open.erase(open.begin() + vertToDel);
		}

		shortestDist = INF;
		vertToDel = INF;

		if (currentVert == end)
			pathFound = true;

		adjVerts(currentVert, adjVert);
		for (int i = 0; i < adjVert.size(); i++)
		{
			if (vertices[currentVert].distFromSrc + adjVert[i].weight < vertices[adjVert[i].vert].distFromSrc)	//update distFromSrc and hDist
			{
				vertices[adjVert[i].vert].distFromSrc = vertices[currentVert].distFromSrc + adjVert[i].weight;
				vertices[adjVert[i].vert].prev = &vertices[currentVert];

				//gets the number of tiles between the two vertices
				hX = vertices[end].x - vertices[adjVert[i].vert].x;
				hY = vertices[end].y - vertices[adjVert[i].vert].y;

				if (hX < 0)
					hX = 0 - hX;
				if (hY < 0)
					hY = 0 - hY;
				//---------------------------------------------------

				vertices[adjVert[i].vert].hDist = vertices[adjVert[i].vert].distFromSrc + (hX + hY);	//heuristic value
			}

			for (int e = 0; e < open.size(); e++)
			{
				if (adjVert[i].vert == open[e])
					inOpen = true;
			}
			if (!vertices[adjVert[i].vert].closed && !inOpen)
			{
				open.push_back(vertices[adjVert[i].vert].vert);
			}
			inOpen = false;
		}
		vertices[currentVert].closed = true;	//close current vertex before choosing a new one

		cout << endl << "size: " << open.size();
		if (open.size() == 0)
		{
			cout << endl << "No path found!" << endl;
			return false;
		}

	} while (!pathFound);

	//displays path
	path.push_back(vertices[end]);
	while (path[path.size() - 1].prev != NULL)
	{
		path.push_back(*path[path.size() - 1].prev);
	}
	cout << "start: " << vertices[start].vert << endl << "end: " << vertices[end].vert << endl;
	for (int i = path.size() - 1; i >= 0; i--)
	{
		//cout << endl << path[i].vert;
		p.push_back({ path[i].x,path[i].y });
	}
	//----------------------------------------
	return true;

	//debugging purposes
	/*
	int count = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].open == false)
			count++;
	}
	cout << endl << "total vertices: " << vertices.size() << endl << "vertices visited: " << count;
	*/
}
void Graph::resetGraph() 
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].distFromSrc != INF)
		{
			vertices[i].distFromSrc = INF;
			vertices[i].hDist = INF;
			vertices[i].prev = NULL;
			vertices[i].closed = false;
		}
	}
	for (int i = 0; i < walls.size(); i++)
	{
		vertices[walls[i]].closed = true;
	}

}
void Graph::getWalls(vector<int>&w)
{
	if (w.size() > 0)
		w.clear();
	for (int i = 0; i < walls.size(); i++)
	{
		w.push_back(walls[i]);
	}
}












