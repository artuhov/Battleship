#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include "GamePlay.h"

int main()
{
	srand(time(NULL));

	GamePlay game;
	
	if (game.setShipsPlayer() == false)
	{
		std::cout << "Goodbye!\n";
		return 0;
	};
	game.setShipsComputer();

	game.start();

	system("pausen");
	return 0;
}