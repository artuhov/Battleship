#include "ComputerSetShips.h"

<<<<<<< HEAD
//good methdod  rkjerj
=======
>>>>>>> parent of b97fbb9... we need this
void ComputerSetShips::setShipRecursion(Ship::TubesShip nTubes, Board& board)
{
	Ship ship(nTubes);
	if (checkShip(ship, board))
		insertShip(ship, board);
	else
		setShipRecursion(nTubes, board);
}
