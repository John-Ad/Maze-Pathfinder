#include "Game_Engine.h"

int main()
{
	Game_Engine game;
	while (game.isRunning())
	{
		game.update();
		game.render();
	}
	return 0;
}