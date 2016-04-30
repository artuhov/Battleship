#include <iostream>
#include "game.h"

game::parametersOFgame game::make_a_move(seaboard& obj, int move_x, int move_y)
{
	switch (obj.return_value_on_board(move_x, move_y))
	{
	case seaboard::emptyCell:
		std::cout << "make a move to (" << move_x << ", " << move_y << ")\n";
		obj.add_value_on_board(move_x, move_y, seaboard::bossShot);
		return miss;

	case seaboard::insertedShip:
		std::cout << "make a move to (" << move_x << ", " << move_y << ")\n";
		obj.add_value_on_board(move_x, move_y, seaboard::strickenShip);
		if (obj.checking_kill_ship(move_x, move_y))
		{
			obj.mark_kill_ship(move_x, move_y);
			if (obj.winning_check())
				return gameover;
			return shipKill;
		}
		return hitShip;

	case seaboard::strickenShip:
	case seaboard::bossShot:
		return missfire;
	}
}

game::parametersOFgame game::finish_kill_ship(seaboard& obj, int move_x, int move_y)
{
	static int index = 1;

	// looking for the ship horizontally right
	static bool flagHorizontRight = true;
	while (flagHorizontRight)
	{
		if (move_x + index > 10)
		{
			index = 1;
			flagHorizontRight = false;
			break;
		}
		switch (make_a_move(obj, move_x + index, move_y))
		{
		case gameover:
			return gameover;
		case shipKill:
			flagHorizontRight = true;
			index = 1;
			return shipKill;
		case hitShip:
			index++;
			break;
		case missfire:
			flagHorizontRight = false;
			index = 1;
			break;
		case miss:
			flagHorizontRight = false;
			index = 1;
			return miss;
		}
	}
	// looking for the ship horizontally left
	static bool flagHorizontLeft = true;
	while (flagHorizontLeft)
	{
		if (move_x - index < 1)
		{
			index = 1;
			flagHorizontLeft = false;
			break;
		}
		switch (make_a_move(obj, move_x - index, move_y))
		{
		case gameover:
			return gameover;
		case shipKill:
			flagHorizontRight = true;
			flagHorizontLeft = true;
			index = 1;
			return shipKill;
		case hitShip:
			index++;
			break;
		case missfire:
			flagHorizontLeft = false;
			index = 1;
			break;
		case miss:
			flagHorizontLeft = false;
			index = 1;
			return miss;
		}
	}
	// looking for the ship vertical up
	static bool flagVerticalUp = true;
	while (flagVerticalUp)
	{
		if (move_y + index > 10)
		{
			index = 1;
			flagVerticalUp = false;
			break;
		}
		switch (make_a_move(obj, move_x, move_y + index))
		{
		case gameover:
			return gameover;
		case shipKill:
			flagHorizontRight = true;
			flagHorizontLeft = true;
			flagVerticalUp = true;
			index = 1;
			return shipKill;
		case hitShip:
			index++;
			break;
		case missfire:
			flagVerticalUp = false;
			index = 1;
			break;
		case miss:
			flagVerticalUp = false;
			index = 1;
			return miss;
		}
	}

	// looking for the ship vertical down
	static bool flagVerticaltDown = true;
	while (flagVerticaltDown)
	{
		if (move_y - index < 1)
		{
			index = 1;
			flagVerticaltDown = false;
			break;
		}
		switch (make_a_move(obj, move_x, move_y - index))
		{
		case gameover:
			return gameover;
		case shipKill:
			flagHorizontRight = true;
			flagHorizontLeft = true;
			flagVerticalUp = true;
			flagVerticaltDown = true;
			index = 1;
			return shipKill;
		case hitShip:
			index++;
			break;
		}
	}
}

void game::show_game_boards(bool showPlayerShip, bool showComputerShip)
{
	std::cout << "player board: \n";
	player.show_board(showPlayerShip);
	std::cout << "computer board: \n";
	computer.show_board(showComputerShip);
}


bool game::hello_player()
{
	std::cout << "\t\t _____   H e l l o !    I t    i s    S E A    B A T T L E    G A M E   _____\n\n";
	std::cout << "Do you want enter ships random (r) or by yourself (y)? \n";
	std::cout << "press (r), (y) or (q)-quit: ";

	char symbol;
	std::cin >> symbol;

	switch (symbol)
	{
	case 'r':
	case 'R':
		player.add_ships_random();
		std::cout << std::endl;
		return true;
	case 'y':
	case 'Y':
		player.add_ships_manual();
		std::cout << std::endl;
		return true;
	default:
		return false;
	}
}

void game::computer_hello()
{
	computer.add_ships_random();
	std::cout << std::endl;
}

void game::game_started()
{
	std::cout << "G A M E   S T A R T E D \n\n";
	parametersOFgame playerDetector = missfire;
	parametersOFgame compDetector = missfire;

	while (true)
	{
		show_game_boards(1, 0);

		// the beginning of a player's turn
		while (playerDetector == shipKill || playerDetector == hitShip || playerDetector == missfire)
		{
			std::cout << "make you choice (enter x, y): ";
			int x;
			int y;
			std::cin >> x >> y;
			if (x > 10 || x < 1 || y > 10 || y < 1)
				continue;
			playerDetector = make_a_move(computer, x, y);
			show_game_boards(1, 0);
		}

		if (playerDetector == miss)
			playerDetector = missfire; // set default

		if (playerDetector == gameover)
		{
			std::cout << "player WIN !!!\n";
			break;
		}
		// the end of a player's turn


		// the beginning of a computer's turn
		while (compDetector == shipKill || compDetector == hitShip || compDetector == missfire)
		{
			static bool hitShipStatus = false;
			static int move_x;
			static int move_y;

			if (!hitShipStatus)
			{
				move_x = rand() % 10 + 1;
				move_y = rand() % 10 + 1;

				compDetector = make_a_move(player, move_x, move_y);
				if (compDetector == hitShip)
					hitShipStatus = true;
				if (compDetector == shipKill)
					std::cout << "computer kill your ship!\a\n";
			}
			else
			{
				compDetector = finish_kill_ship(player, move_x, move_y);
				if (compDetector == shipKill)
				{
					hitShipStatus = false;
					std::cout << "computer kill your ship!\a\n";
				}
			}
		}

		if (compDetector == miss)
			compDetector = missfire; // set default

		if (compDetector == gameover)
		{
			std::cout << "Computer WIN !!!\n";
			break;
		}
		// the end of a computer's turn
	}
}
