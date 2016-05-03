#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "Board.h"

Board::Board()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			board[i][j] = static_cast<int> (EMPTY_CELL);
}
void Board::showBoard(bool shipShow) const
{
	std::cout << "  x|1 2 3 4 5 6 7 8 9 10\n";
	std::cout << " y_|____________________\n";

	for (int i = 1; i < BOARD_SIZE - 1; i++)
	{
		std::cout << std::setw(2) << i << " |";
		for (int j = 1; j < BOARD_SIZE - 1; j++)
			switch (board[i][j])
			{
			case EMPTY_CELL:
				std::cout << ". ";
				break;
			case INSERTED_SHIP:
				if (shipShow)
					std::cout << static_cast <char>(-2) << " ";
				else
					std::cout << ". ";
				break;
			case STRICKEN_SHIP:
				std::cout << static_cast <char>(-8) << " ";
				break;
			case BOSS_SHOT:
				std::cout << "x ";
				break;
			}
		std::cout << "| \n";
	}
	std::cout << "   |____________________|\n\n";
}

bool Board::checkShipKill2(Movement movement)
{
	BoardParametrs shoot = static_cast<BoardParametrs> (board[movement.getMovementY()][movement.getMovementX()]);
	while (shoot != EMPTY_CELL && shoot != BOSS_SHOT)
	{
		if (shoot == INSERTED_SHIP)
			return false;
		movement++;
		shoot = static_cast<BoardParametrs> (board[movement.getMovementY()][movement.getMovementX()]);
	}
	return true;
}

bool Board::checkShipKill(const Move& move)
{
	bool check = checkShipKill2(Movement(move, Movement::NONE, Movement::POSITIVE));
	check &= checkShipKill2(Movement(move, Movement::NONE, Movement::NEGATIVE));
	check &= checkShipKill2(Movement(move, Movement::POSITIVE, Movement::NONE));
	check &= checkShipKill2(Movement(move, Movement::NEGATIVE, Movement::NONE));
	return check;
}

void Board::markShipKill2(int moveX, int moveY, Movement::Direction direction)
{
	int i = 0;
	do {
		board[moveY + i * direction][moveX + 1] = BOSS_SHOT;
		board[moveY + i * direction][moveX - 1] = BOSS_SHOT;
	} while (board[moveY + direction * i++][moveX] == STRICKEN_SHIP);
	board[moveY + (i - 1) * direction][moveX] = BOSS_SHOT;
}
void Board::markShipKill3(int moveX, int moveY, Movement::Direction direction)
{
	int i = 0;
	do {
		board[moveY + 1][moveX + i * direction] = BOSS_SHOT;
		board[moveY - 1][moveX + i * direction] = BOSS_SHOT;
	} while (board[moveY][moveX + direction * i++] == STRICKEN_SHIP);
	board[moveY][moveX + (i - 1) * direction] = BOSS_SHOT;
}

void Board::markShipKill(int moveX, int moveY)
{

	//mark horizontal coordinates to the rightward and leftward
	if (board[moveY][moveX + 1] != STRICKEN_SHIP && board[moveY][moveX - 1] != STRICKEN_SHIP)
	{
		markShipKill2(moveX, moveY, Movement::POSITIVE);
		markShipKill2(moveX, moveY, Movement::NEGATIVE);
	}

	//mark upright coordinates to the upward and downward
	else
	{
		markShipKill3(moveX, moveY, Movement::POSITIVE);
		markShipKill3(moveX, moveY, Movement::NEGATIVE);
	}
}
bool Board::checkWinnig()
{
	for (int i = 1; i < BOARD_SIZE - 1; i++)
		for (int j = 1; j < BOARD_SIZE - 1; j++)
			if (board[i][j] == INSERTED_SHIP)
				return false;
	return true;
}
