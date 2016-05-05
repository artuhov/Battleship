#include <iostream>
#include "ManualSetShips.h"

void ManualSetShips::setShip(Ship::TubesShip nTubes, Board& board)
{
	std::cout << "You enter " << nTubes << "-tube ship \n";

	std::cout << "Enter starting coordinates and horizontally(0) or vertical(1) direction: (x, y, d): ";
	int startX;
	int startY;
	int direction;
	std::cin >> startX >> startY >> direction;

	Ship ship(startX, startY, nTubes, static_cast<Ship::Direction>(direction));

	if (checkShip(ship, board))
	{
		insertShip(ship, board);
		board.showBoard(Board::SHOW);
	}
	else
		setShip(nTubes, board);
}
