#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "game.h"


int main()
{
	game battleship;
	srand(time(NULL));
	if (battleship.hello_player() == false)
	{
		std::cout << "Goodbye!\n";
		return 0;
	};
	battleship.computer_hello();
	battleship.game_started();
	
	return 0;
}