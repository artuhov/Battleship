#include <cmath>
#include "BaseSetShips.h"

bool BaseSetShips::checkShip(const Ship& ship, const Board& board) const
{

//cool game
	int startX = ship.getStartX();
	int startY = ship.getStartY();
	int endX = ship.getEndX();
	int endY = ship.getEndY();

	bool endBoard = startX > 10 || startY > 10 || endX > 10 || endY > 10;
	bool beforBoard = startX < 1 || startY < 1 || endX < 1 || endY < 1;

	if (endBoard || beforBoard)		// error not on board or end of board
		return false;

	const int SHIP_SIZE_ROUND = 3;

	if (startY == endY)  // the ship is positioned upright
	{
		int index = startX <= endX ? startX : endX;
		int sum = 0;
		for (int i = 0; i < SHIP_SIZE_ROUND; i++)
			for (int j = 0; j < abs(startX - endX) + SHIP_SIZE_ROUND; j++)
				sum += board.getValue(index - 1 + j, startY - 1 + i);
		return sum == 0;
	}
	if (startX == endX) // the ship is positioned horizontally
	{
		int index = startY < endY ? startY : endY;
		int sum = 0;
		for (int i = 0; i < abs(startY - endY) + SHIP_SIZE_ROUND; i++)
			for (int j = 0; j < SHIP_SIZE_ROUND; j++)
				sum += board.getValue(startX - 1 + j, index - 1 + i);
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
	setShip(Ship::FOURTUBE, 1, board);
	setShip(Ship::THREETUBE, 2, board);
	setShip(Ship::TWOTUBE, 3, board);
	setShip(Ship::MONOTUBE, 4, board);
}
void BaseSetShips::setShip(Ship::TubesShip nTubes, int nShips, Board& board)
{
	for (int i = 0; i < nShips; i++)
		setShip(nTubes, board);
}
BaseSetShips::~BaseSetShips()
{

};
