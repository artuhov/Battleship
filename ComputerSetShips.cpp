#include "ComputerSetShips.h"

//good method
void ComputerSetShips::setShipRecursion(Ship::TubesShip nTubes, Board& board)
{
	Ship ship(nTubes);
	if (checkShip(ship, board))
		insertShip(ship, board);
	else
	//sdhjfjhfhjffhjjfhfjh
		setShipRecursion(nTubes, board);
}
