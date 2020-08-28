#pragma once
//#include "Include.h"
#include "Graph.h"

class Map
{
private:
	struct Grid
	{
		int* x;
		int* y;
	};
	struct Wall {
		RectangleShape wall;
		int x;
		int y;
	};

	vector<Wall> walls;

	int numOftiles;

	void initWalls();
	void initGraph(int size, int width, int height);
public:
	//constructor/destructor
	Map(int wX, int wY, int tileSize);
	~Map();

	Grid grid;
	Graph* graph;
	vector<int> wPos;		//walls

	int width;
	int height;

	//draw function
	void drawMap(RenderWindow* window);

	//return functions
	int getNumOftiles();
};


//	To do: replace current grid system with one that has only a single set of unique x and y values
