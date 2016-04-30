#pragma once
#include "seaboard.h"

class game
{
private:
	enum  parametersOFgame { gameover, shipKill, hitShip, missfire, miss };
	seaboard player;
	seaboard computer;
	parametersOFgame make_a_move(seaboard& obj, int move_x, int move_y);
	parametersOFgame finish_kill_ship(seaboard& obj, int _move_x, int _move_y);
	void show_game_boards(bool showPlayerShip, bool showComputerShip);

public:
	bool hello_player();
	void computer_hello();
	void game_started();
};

