#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Game.h"

int main()
{
	srand(time(NULL));

	Game game;
	
	if (game.setShipsPlayer() == false)
	{
		std::cout << "Goodbye!\n";
		return 0;
	};
	game.setShipsComputer();

	game.start();
	
	return 0;
}