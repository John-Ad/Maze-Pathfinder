#include "Snake.h"



//___constructor/destructor______
Snake::Snake(int x[], int y[], int w, int h, int maxSz)
{
	//snake initialization
	height = h;
	width = w;

	maxSize = maxSz;
	snakeX = new int[maxSize];
	snakeY = new int[maxSize];

	snake.push_back(RectangleShape());
	snake[0].setFillColor(Color::Red);
	snake[0].setSize(Vector2f(w, h));
	snake[0].setPosition(Vector2f(x[1], y[1]));

	//food initialization
	food.f.setFillColor(Color::Green);
	food.f.setSize(Vector2f(w, h));
	
	srand(time(NULL));
}
Snake::~Snake()
{
	delete snakeX;
	delete snakeY;
}

//____move_function_____________
void Snake::changeDir(int opt)
{
	switch (opt)
	{
	case 0:					//right
		right = true;
		left = false;
		up = false;
		down = false;
		break;
	case 1:					//left
		right = false;
		left = true;
		up = false;
		down = false;
		break;
	case 2:					//up
		right = false;
		left = false;
		up = true;
		down = false;
		break;
	case 3:					//down
		right = false;
		left = false;
		up = false;
		down = true;
		break;
	}
}

//____update_and_draw_functions
void Snake::updateSnake(int x[], int y[], bool update, Map* map)
{
	if (path.size() == 0)
	{
		bool pathFound = false;
		int foodPos = 0;
		do
		{
			foodPos = spawnFood(map->grid.x, map->grid.y, map);
			pathFound = map->graph->shortestPath(fPos, foodPos, path);
			map->graph->resetGraph();
		} while (!pathFound);
		fPos = foodPos;
	}
	if (update)
	{
		/*	used for a snake of length > 1
		for (int i = 1; i < snake.size(); i++)
		{
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
			snake[i].setPosition(Vector2f(snakeX[i], snakeY[i]));
		}
		*/

		//cout << endl << path[0].first << ", " << path[0].second;
		
		snake[0].setPosition(Vector2f(path[0].first, path[0].second));
		path.erase(path.begin());
	}
}
void Snake::drawSnakeAndFood(RenderWindow* window)
{
	window->draw(food.f);
	for (RectangleShape i : snake)
	{
		window->draw(i);
	}
}


//___Food_functions
int Snake::spawnFood(int x[], int y[], Map* map)
{
	bool randMatch;
	do
	{
		randMatch = false;
		food.x = rand() % (map->width - 1) + 0;
		food.y = rand() % (map->height - 1) + 0;
		for (int i = 0; i < map->wPos.size(); i++)
		{
			if (food.x + (map->width*food.y) == map->wPos[i])
				randMatch = true;
		}
	} while (randMatch);


	cout << food.x << ", " << food.y << endl;

	food.f.setPosition(Vector2f(x[food.x], y[food.y]));

	return food.x + (map->width*food.y);		//converts the x and y positions into one number representing the position in a list //this is used with the graph
}














