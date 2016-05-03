#include "RandomSetShips.h"

void RandomSetShips::setShip(Ship::TubesShip nTubes, Board& board)
{
	Ship ship(nTubes);

	if (checkShip(ship, board))
		insertShip(ship, board);
	else
		setShip(nTubes, board);
}
