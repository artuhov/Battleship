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
bool Board::checkShipKill(int moveX, int moveY)
{
	int i = 0;
	//check upright coordinates to the downward
	while (board[moveY + i + 1][moveX] != EMPTY_CELL && board[moveY + i + 1][moveX] != BOSS_SHOT)
	{
		if (board[moveY + i + 1][moveX] == INSERTED_SHIP)
			return false;
		i++;
	}

	i = 0;
	//check upright coordinates to the upward
	while (board[moveY - i - 1][moveX] != EMPTY_CELL && board[moveY - i - 1][moveX] != BOSS_SHOT)
	{
		if (board[moveY - i - 1][moveX] == INSERTED_SHIP)
			return false;
		i++;
	}

	i = 0;
	//check horizontal coordinates to the rightward
	while (board[moveY][moveX + i + 1] != EMPTY_CELL && board[moveY][moveX + i + 1] != BOSS_SHOT)
	{
		if (board[moveY][moveX + i + 1] == INSERTED_SHIP)
			return false;
		i++;
	}

	i = 0;
	//check horizontal coordinates to the leftward
	while (board[moveY][moveX - i - 1] != EMPTY_CELL && board[moveY][moveX - i - 1] != BOSS_SHOT)
	{
		if (board[moveY][moveX - i - 1] == INSERTED_SHIP)
			return false;
		i++;
	}
	return true;
}
void Board::markShipKill(int moveX, int moveY)
{
	int i;
	//mark horizontal coordinates to the rightward and leftward
	if (board[moveY][moveX + 1] != STRICKEN_SHIP && board[moveY][moveX - 1] != STRICKEN_SHIP)
	{
		i = 0;
		do {
			board[moveY + i][moveX + 1] = BOSS_SHOT;
			board[moveY + i][moveX - 1] = BOSS_SHOT;
		} while (board[moveY + i++][moveX] == STRICKEN_SHIP);
		board[moveY + i - 1][moveX] = BOSS_SHOT;

		i = 0;
		do {
			board[moveY - i][moveX + 1] = BOSS_SHOT;
			board[moveY - i][moveX - 1] = BOSS_SHOT;
		} while (board[moveY - i++][moveX] == STRICKEN_SHIP);
		board[moveY - (i - 1)][moveX] = BOSS_SHOT;
	}

	//mark upright coordinates to the upward and downward
	else
	{
		i = 0;
		do {
			board[moveY + 1][moveX + i] = BOSS_SHOT;
			board[moveY - 1][moveX + i] = BOSS_SHOT;
		} while (board[moveY][moveX + i++] == STRICKEN_SHIP);
		board[moveY][moveX + i - 1] = BOSS_SHOT;

		i = 0;
		do {
			board[moveY + 1][moveX - i] = BOSS_SHOT;
			board[moveY - 1][moveX - i] = BOSS_SHOT;
		} while (board[moveY][moveX - i++] == STRICKEN_SHIP);
		board[moveY][moveX - (i - 1)] = BOSS_SHOT;
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
