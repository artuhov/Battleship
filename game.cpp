#include <iostream>
#include <memory>
#include "Game.h"

Game::GameParametrs Game::makeMove(Board& board, int moveX, int moveY)
{
	switch (board.getValue(moveX, moveY))
	{
	case Board::EMPTY_CELL:
		std::cout << "make a move to (" << moveX << ", " << moveY << ")\n";
		board.setValue(moveX, moveY, Board::BOSS_SHOT);
		return MISS;

	case Board::INSERTED_SHIP:
		std::cout << "make a move to (" << moveX << ", " << moveY << ")\n";
		board.setValue(moveX, moveY, Board::STRICKEN_SHIP);
		if (board.checkShipKill(moveX, moveY))
		{
			board.markShipKill(moveX, moveY);
			if (board.checkWinnig())
				return GAMEOVER;
			return SHIP_KILL;
		}
		return HIT_SHIP;

	case Board::STRICKEN_SHIP:
	case Board::BOSS_SHOT:
		return MISS_FIRE;
	}
}
Game::GameParametrs Game::finishShipKill(Board& board, int moveX, int moveY)
{
	static int index = 1;

	// looking for the ship horizontally right
	static bool flagHorizontRight = true;
	while (flagHorizontRight)
	{
		if (moveX + index > 10)
		{
			index = 1;
			flagHorizontRight = false;
			break;
		}
		switch (makeMove(board, moveX + index, moveY))
		{
		case GAMEOVER:
			return GAMEOVER;
		case SHIP_KILL:
			flagHorizontRight = true;
			index = 1;
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		case MISS_FIRE:
			flagHorizontRight = false;
			index = 1;
			break;
		case MISS:
			flagHorizontRight = false;
			index = 1;
			return MISS;
		}
	}
	// looking for the ship horizontally left
	static bool flagHorizontLeft = true;
	while (flagHorizontLeft)
	{
		if (moveX - index < 1)
		{
			index = 1;
			flagHorizontLeft = false;
			break;
		}
		switch (makeMove(board, moveX - index, moveY))
		{
		case GAMEOVER:
			return GAMEOVER;
		case SHIP_KILL:
			flagHorizontRight = true;
			flagHorizontLeft = true;
			index = 1;
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		case MISS_FIRE:
			flagHorizontLeft = false;
			index = 1;
			break;
		case MISS:
			flagHorizontLeft = false;
			index = 1;
			return MISS;
		}
	}
	// looking for the ship vertical up
	static bool flagVerticalUp = true;
	while (flagVerticalUp)
	{
		if (moveY + index > 10)
		{
			index = 1;
			flagVerticalUp = false;
			break;
		}
		switch (makeMove(board, moveX, moveY + index))
		{
		case GAMEOVER:
			return GAMEOVER;
		case SHIP_KILL:
			flagHorizontRight = true;
			flagHorizontLeft = true;
			flagVerticalUp = true;
			index = 1;
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		case MISS_FIRE:
			flagVerticalUp = false;
			index = 1;
			break;
		case MISS:
			flagVerticalUp = false;
			index = 1;
			return MISS;
		}
	}

	// looking for the ship vertical down
	static bool flagVerticaltDown = true;
	while (flagVerticaltDown)
	{
		if (moveY - index < 1)
		{
			index = 1;
			flagVerticaltDown = false;
			break;
		}
		switch (makeMove(board, moveX, moveY - index))
		{
		case GAMEOVER:
			return GAMEOVER;
		case SHIP_KILL:
			flagHorizontRight = true;
			flagHorizontLeft = true;
			flagVerticalUp = true;
			flagVerticaltDown = true;
			index = 1;
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		}
	}
}
void Game::showGameBoards(bool showPlayerShip, bool showComputerShip)
{
	std::cout << "player board: \n";
	player.showBoard(showPlayerShip);
	std::cout << "computer board: \n";
	computer.showBoard(showComputerShip);
}
bool Game::setShipsPlayer()
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
		{
			std::unique_ptr<BaseSetShips> uniqPtr (new ComputerSetShips());
			uniqPtr->setShip(player);
			std::cout << std::endl;
			return true;
		}
		case 'y':
		case 'Y':
		{
			std::unique_ptr<BaseSetShips> uniqPtr(new PlayerSetShips());
			uniqPtr->setShip(player);
			std::cout << std::endl;
			return true;
		}
		default:
			return false;
		}
}
void Game::setShipsComputer()
{
	std::unique_ptr<BaseSetShips> uniqPtr(new ComputerSetShips());
	uniqPtr->setShip(computer);
	std::cout << std::endl;
}
void Game::start()
{
	std::cout << "G A M E   S T A R T E D \n\n";
	GameParametrs playerDetector = MISS_FIRE;
	GameParametrs computerDetector = MISS_FIRE;

	while (true)
	{
		showGameBoards(1, 0);

		// the beginning of a player's turn
		while (playerDetector == SHIP_KILL || playerDetector == HIT_SHIP || playerDetector == MISS_FIRE)
		{
			std::cout << "make you choice (enter x, y): ";
			int x;
			int y;
			std::cin >> x >> y;
			if (x > 10 || x < 1 || y > 10 || y < 1)
				continue;
			playerDetector = makeMove(computer, x, y);
			showGameBoards(1, 0);
		}

		if (playerDetector == MISS)
			playerDetector = MISS_FIRE; // set default

		if (playerDetector == GAMEOVER)
		{
			std::cout << "player WIN !!!\n";
			break;
		}
		// the end of a player's turn


		// the beginning of a computer's turn
		while (computerDetector == SHIP_KILL || computerDetector == HIT_SHIP || computerDetector == MISS_FIRE)
		{
			static bool hitShipStatus = false;
			static int moveX;
			static int moveY;

			if (!hitShipStatus)
			{
				moveX = rand() % 10 + 1;
				moveY = rand() % 10 + 1;

				computerDetector = makeMove(player, moveX, moveY);
				if (computerDetector == HIT_SHIP)
					hitShipStatus = true;
				if (computerDetector == SHIP_KILL)
					std::cout << "computer kill your ship!\a\n";
			}
			else
			{
				computerDetector = finishShipKill(player, moveX, moveY);
				if (computerDetector == SHIP_KILL)
				{
					hitShipStatus = false;
					std::cout << "computer kill your ship!\a\n";
				}
			}
		}

		if (computerDetector == MISS)
			computerDetector = MISS_FIRE; // set default

		if (computerDetector == GAMEOVER)
		{
			std::cout << "Computer WIN !!!\n";
			break;
		}
		// the end of a computer's turn
	}
}
