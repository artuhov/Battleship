#include <cmath>
#include "BaseSetShips.h"

bool BaseSetShips::checkShip(const Ship& ship, const Board& board) const
{

	int begin_x = ship.getStartX();
	int begin_y = ship.getStartY();
	int end_x = ship.getEndX();
	int end_y = ship.getEndY();

	if (begin_x > 10 || begin_y > 10 || end_x > 10 || end_y > 10 ||
		begin_x < 1 || begin_y < 1 || end_x < 1 || end_y < 1)		// error not on board or end of board
		return false;

	const int ship_size_round = 3;

	if (begin_y == end_y)  // the ship is positioned upright
	{
		int index = begin_x <= end_x ? begin_x : end_x;
		int sum = 0;
		for (int i = 0; i < ship_size_round; i++)
			for (int j = 0; j < abs(begin_x - end_x) + ship_size_round; j++)
				sum += board.getValue(index - 1 + j, begin_y - 1 + i);
		return sum == 0;
	}
	if (begin_x == end_x) // the ship is positioned horizontally
	{
		int index = begin_y < end_y ? begin_y : end_y;
		int sum = 0;
		for (int i = 0; i < abs(begin_y - end_y) + ship_size_round; i++)
			for (int j = 0; j < ship_size_round; j++)
				sum += board.getValue(begin_x - 1 + j, index - 1 + i);
		return sum == 0;
	}
	return false;
}
void BaseSetShips::insertShip(const Ship& ship, Board& board)
{
	int startX = ship.getStartX();
	int startY = ship.getStartY();
	int endX = ship.getEndX();
	int endY = ship.getEndY();

	if (startX == endX) // the ship is positioned upright or monotube ship
	{
		int index = startY <= endY ? startY : endY;
		for (int i = 0; i <= abs(startY - endY); i++)
			board.setValue(startX, index + i, Board::INSERTED_SHIP);
	}
	if (startY == endY)  // the ship is positioned horizontally
	{
		int index = startX < endX ? startX : endX;
		for (int i = 0; i <= abs(startX - endX); i++)
			board.setValue(index + i, startY, Board::INSERTED_SHIP);
	}
}
void BaseSetShips::setShip(Board& board)
{
	setShipLoop(Ship::FOURTUBE, 1, board);
	setShipLoop(Ship::THREETUBE, 2, board);
	setShipLoop(Ship::TWOTUBE, 3, board);
	setShipLoop(Ship::MONOTUBE, 4, board);
}
void BaseSetShips::setShipLoop(Ship::TubesShip nTubes, int nShips, Board& board)
{
	for (int i = 0; i < nShips; i++)
		setShipRecursion(nTubes, board);
}
BaseSetShips::~BaseSetShips() 
{

};