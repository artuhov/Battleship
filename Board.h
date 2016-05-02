#pragma once
#include "Ship.h"

class Board
{
public:
	Board();
	enum  ParametrsONboard { EMPTY_CELL, INSERTED_SHIP, STRICKEN_SHIP, BOSS_SHOT };
	void setValue(int moveX, int moveY, ParametrsONboard value)
	{
		board[moveY][moveX] = static_cast<int> (value);
	}
	int getValue(int moveX, int moveY) const
	{
		return board[moveY][moveX];
	}
	void showBoard(bool shipShow) const;
	bool checkShipKill(int moveX, int moveY);
	void markShipKill(int moveX, int moveY);
	bool checkWinnig();

private:
	static const int BOARD_SIZE = 12;
	int board[BOARD_SIZE][BOARD_SIZE];
};

