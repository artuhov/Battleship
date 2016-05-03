#pragma once
#include "Ship.h"
#include "Board.h"
#include "BaseSetShips.h"

class RandomSetShips : public BaseSetShips
{
protected:	
	virtual void setShip(Ship::TubesShip nTubes, Board& board);

};
