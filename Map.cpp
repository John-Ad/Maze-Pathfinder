#include "Map.h"


Map::Map(int wX, int wY, int tileSize)
{
	width = wX / tileSize;
	height = wY / tileSize;

	grid.x = new int[wX / tileSize];
	grid.y = new int[wY / tileSize];

	int xVal = 0;
	int yVal = 0;

	for (int i = 0; i < wX / tileSize; i++)
	{
		grid.x[i] = xVal;
		xVal += tileSize;
	}
	for (int i = 0; i < wY / tileSize; i++)
	{
		grid.y[i] = yVal;
		yVal += tileSize;
	}

	numOftiles = (wX / tileSize) * (wY / tileSize);

	initGraph(numOftiles, wX / tileSize, wY / tileSize);
	initWalls();
}
Map::~Map()
{
	delete grid.x;
	delete grid.y;

}

void Map::initGraph(int size, int width, int height)
{
	graph = new Graph(size, grid.x, grid.y, width);
	graph->populateList(width);
	//graph->shortestPath(1560, 1599, p);
}
void Map::initWalls()
{
	int x = 0;
	int y = 0;

	Wall wll;
	wll.wall.setFillColor(Color::Cyan);
	wll.wall.setSize(Vector2f(20, 20));

	graph->getWalls(wPos);
	for (int i = 0; i < wPos.size(); i++)
	{
		x = wPos[i] % width;
		y = wPos[i] / width;
		wll.x = x;
		wll.y = y;
		wll.wall.setPosition(Vector2f(grid.x[x], grid.y[y]));

		walls.push_back(wll);
	}
}

void Map::drawMap(RenderWindow* window)
{
	for (Wall i:walls)
	{
		window->draw(i.wall);
	}
}
int Map::getNumOftiles()
{
	return numOftiles;
}






