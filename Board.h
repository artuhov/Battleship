#pragma once
#include "Ship.h"
#include "Move.h"
#include "Movement.h"

class Board
{
public:
	Board();
	enum  BoardParametrs { EMPTY_CELL, INSERTED_SHIP, STRICKEN_SHIP, BOSS_SHOT };
	void setValue(int moveX, int moveY, BoardParametrs value)
	{
		board[moveY][moveX] = static_cast<int> (value);
	}
	int getValue(int moveX, int moveY) const
	{
		return board[moveY][moveX];
	}
	void showBoard(bool shipShow) const;
	bool isShipKilled(const Move& move);
	void markKilledShip(int moveX, int moveY);
	bool checkWinnig();

private:
	static const int BOARD_SIZE = 12;
	int board[BOARD_SIZE][BOARD_SIZE];
	bool checkShipKilled(Movement movement);
	void markShipAround(int moveX, int moveY, Movement::Direction direction);
	void markShipKill3(int moveX, int moveY, Movement::Direction direction);

};

