#pragma once
//#include "Include.h"
//#include "Map.h"
#include "Snake.h"



class Game_Engine
{
private:
	//window variables
	RenderWindow* window;
	VideoMode vm;
	Event ev;

	int fRate{ 30 };
	int windowX{ 400 };
	int windowY{ 400 };

	//map variables
	Map* gameMap;

	//snake variables
	Snake* snake;
	
	//init functions
	void initMap();
	void initWindow();
	void initSnake();

	//frame rate function
	bool nextFrame();

	//update__and__render__functions
	void pollEvent();

public:
	//constructor/destructor
	Game_Engine();
	~Game_Engine();

	bool isRunning();

	void update();
	void render();
};

