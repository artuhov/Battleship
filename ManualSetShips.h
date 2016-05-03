#pragma once
#include "Ship.h"
#include "Board.h"
#include "BaseSetShips.h"

class ManualSetShips : public BaseSetShips
{
protected:
	virtual void setShip(Ship::TubesShip nTubes, Board& board);

};