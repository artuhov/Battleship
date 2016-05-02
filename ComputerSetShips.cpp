#include "ComputerSetShips.h"

void ComputerSetShips::setShipRecursion(Ship::TubesShip nTubes, Board& board)
{
	Ship ship(nTubes);
	if (checkShip(ship, board))
		insertShip(ship, board);
	else
		setShipRecursion(nTubes, board);
}
