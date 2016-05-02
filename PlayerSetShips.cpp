#include <iostream>
#include "PlayerSetShips.h"

void PlayerSetShips::setShipRecursion(Ship::TubesShip nTubes, Board& board)
{
	std::cout << "You enter " << nTubes << "-tube ship \n";

	std::cout << "Enter starting coordinates and horizontally(0) or upright(1) direction: (x, y, d): ";
	int startX;
	int startY;
	int direction;
	std::cin >> startX >> startY >> direction;

	Ship ship(startX, startY, nTubes, direction);

	if (checkShip(ship, board))
	{
		insertShip(ship, board);
		board.showBoard(1);
	}
	else
		setShipRecursion(nTubes, board);
}
