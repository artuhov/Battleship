#include <iostream>
#include <memory>
#include "GamePlay.h"
#include "Test.h"

GamePlay::GameParametrs GamePlay::makeMove(Board& board, int moveX, int moveY)
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
		if (board.isShipKilled(Move(moveX, moveY)))
		{
			board.markKilledShip(moveX, moveY);
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

GamePlay::GameParametrs GamePlay::finishShipKill(Board& board, int moveX, int moveY)
{
	int index = 1;

	// looking for the ship horizontally right
	static bool flagHorizontRight = true;
	while (flagHorizontRight)
	{
		if (moveX + index > 10)
		{
			flagHorizontRight = false;
			break;
		}
		switch (makeMove(board, moveX + index, moveY))
		{
		case GAMEOVER:
			return GAMEOVER;
		case SHIP_KILL:
			flagHorizontRight = true;
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		case MISS_FIRE:
			flagHorizontRight = false;
			break;
		case MISS:
			flagHorizontRight = false;
			return MISS;
		}
	}
	// looking for the ship horizontally left
	//please fix here
	static bool flagHorizontLeft = true;
	index = 1;
	while (flagHorizontLeft)
	{
		if (moveX - index < 1)
		{
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
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		case MISS_FIRE:
			flagHorizontLeft = false;
			break;
		case MISS:
			flagHorizontLeft = false;
			return MISS;
		}
	}
	// looking for the ship vertical up
	static bool flagVerticalUp = true;
	index = 1;
	while (flagVerticalUp)
	{
		if (moveY + index > 10)
		{
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
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		case MISS_FIRE:
			flagVerticalUp = false;
			break;
		case MISS:
			flagVerticalUp = false;
			return MISS;
		}
	}

	// looking for the ship vertical down
	static bool flagVerticaltDown = true;
	index = 1;
	while (flagVerticaltDown)
	{
		if (moveY - index < 1)
		{
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
			return SHIP_KILL;
		case HIT_SHIP:
			index++;
			break;
		}
	}
}
void GamePlay::showGameBoards(bool showPlayerShip, bool showComputerShip)
{
	//system("cls");
	std::cout << "player board: \n";
	player.showBoard(showPlayerShip);
	std::cout << "computer board: \n";
	computer.showBoard(showComputerShip);
}
bool GamePlay::setShipsPlayer()
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
		std::unique_ptr<BaseSetShips> uniqPtr(new RandomSetShips());
		uniqPtr->setShip(player);
		std::cout << std::endl;
		return true;
	}
	case 'y':
	case 'Y':
	{
		std::unique_ptr<BaseSetShips> uniqPtr(new ManualSetShips());
		uniqPtr->setShip(player);
		std::cout << std::endl;
		return true;
	}
	default:
		return false;
	}
}
void GamePlay::setShipsComputer()
{
	std::unique_ptr<BaseSetShips> uniqPtr(new RandomSetShips());
	uniqPtr->setShip(computer);
	std::cout << std::endl;
}
void GamePlay::start()
{
	std::cout << "G A M E   S T A R T E D \n\n";
	GameParametrs playerDetector = MISS_FIRE;
	GameParametrs computerDetector = MISS_FIRE;

	while (true)
	{
		showGameBoards(Board::SHOW, Board::NOSHOW);

		// the beginning of a player's turn
		while (playerDetector == SHIP_KILL || playerDetector == HIT_SHIP || playerDetector == MISS_FIRE)
		{
			std::cout << "make you choice (enter x, y): ";
			int x;
			int y;
			std::cin >> x >> y;

			//Test test;
			//x = test.getX();
			//y = test.getY();
			
			const int RISE_GAME_BOARD = 1;
			if (x > Board::GAME_BOARD_SIZE || y > Board::GAME_BOARD_SIZE || x < RISE_GAME_BOARD || y < RISE_GAME_BOARD)
				continue;
			playerDetector = makeMove(computer, x, y);
			showGameBoards(Board::SHOW, Board::NOSHOW);
		}

		if (playerDetector == MISS)
			playerDetector = MISS_FIRE; // set default

		if (playerDetector == GAMEOVER)
		{
			showGameBoards(Board::SHOW, Board::NOSHOW);
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
				moveX = 1 + rand() % Board::GAME_BOARD_SIZE;
				moveY = 1 + rand() % Board::GAME_BOARD_SIZE;

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
			showGameBoards(Board::SHOW, Board::NOSHOW);
			std::cout << "Computer WIN !!!\n";
			break;
		}
		// the end of a computer's turn
	}
}
