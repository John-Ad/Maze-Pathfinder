#pragma once
#include "Map.h"

class Snake
{
private:
	//snake variables
	vector<RectangleShape>snake;

	int height;
	int width;
	int maxSize;
	int* snakeX;
	int* snakeY;
	bool left, right, up, down;

	//path variables
	vector<pair<int, int>>path;

	//food variables
	struct Food {
		RectangleShape f;
		int x;
		int y;
	};
	Food food;
	int fPos{ 0 };

public:
	Snake(int x[], int y[], int w, int h, int maxSz);
	~Snake();

	//food public functions
	int spawnFood(int x[], int y[], Map* map);

	//update_and_draw_functions
	void changeDir(int opt);
	void updateSnake(int x[], int y[], bool update, Map* map);
	void drawSnakeAndFood(RenderWindow* window);
};

