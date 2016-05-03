#pragma once
#include "Ship.h"
#include "Board.h"

class BaseSetShips
{
public:
	void setShip(Board& board);
	virtual ~BaseSetShips() = 0;

protected:
	virtual void setShip(Ship::TubesShip nTubes, Board& board)=0;
	void setShip(Ship::TubesShip nTubes, int nShips, Board& board);
	bool checkShip(const Ship& ship, const Board& board) const;
	void insertShip(const Ship& ship, Board& board);
};