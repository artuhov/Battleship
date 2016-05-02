#pragma once
#include "Ship.h"
#include "Board.h"
#include "BaseSetShips.h"

class ComputerSetShips : public BaseSetShips
{
protected:	
	virtual void setShipRecursion(Ship::TubesShip nTubes, Board& board);

};
