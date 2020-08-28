#include "Game_Engine.h"


//_____constructor/destructor______________
Game_Engine::Game_Engine()
{
	initWindow();
	initMap();
	initSnake();
}
Game_Engine::~Game_Engine()
{
	delete window;
	delete gameMap;
	delete snake;
}

//_____init_functions__________
void Game_Engine::initWindow()
{
	vm.height = windowY;
	vm.width = windowX;

	window = new RenderWindow(vm, "Snake AI", Style::Titlebar | Style::Close);
	window->setFramerateLimit(fRate);

	fRate = 0;
}
void Game_Engine::initMap()
{
	gameMap = new Map(windowX, windowY, 20);
}
void Game_Engine::initSnake()
{
	snake = new Snake(gameMap->grid.x, gameMap->grid.y, 20, 20, gameMap->getNumOftiles());
}

//____frame_rate_function________
bool Game_Engine::nextFrame()
{
	fRate += 1;
	if (fRate == 5)
	{
		fRate = 0;
		return true;
	}
	else
		return false;
}


//___loop_control_functions
bool Game_Engine::isRunning()
{
	return window->isOpen();
}


//______update_and_render_functions_____
void Game_Engine::pollEvent()
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case Event::Closed:
			window->close();
			break;
		default:
			break;
		}
	}
}
void Game_Engine::update()
{
	pollEvent();
	snake->updateSnake(gameMap->grid.x, gameMap->grid.y, nextFrame(), gameMap);
}
void Game_Engine::render()
{
	window->clear();
	
	//
	gameMap->drawMap(window);
	snake->drawSnakeAndFood(window);
	//

	window->display();
}



