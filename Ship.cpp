#include <stdlib.h>
#include "Ship.h"

Ship::Ship()
{
	startX_ = 0;
	startY_ = 0;
	endX_ = 0;
	endY_ = 0;
}
Ship::Ship(TubesShip nTubes)
{
	const int BOARD_SIZE = 10;

	startX_ = 1 + rand() % BOARD_SIZE;
	startY_ = 1 + rand() % BOARD_SIZE;
	endX_ = startX_;
	endY_ = (startY_ + nTubes - 1 <= BOARD_SIZE) ? (startY_ + nTubes - 1) : (startY_ - (nTubes - 1));

	if (rand() % 2)		 // change startX with startY and etc for more random results
		changeXY();
}
Ship::Ship(int startX, int startY, TubesShip nTubes, Direction direction) 
{
	startX_ = startX;
	startY_ = startY;

	if (direction == HORIZONTALLY)
	{
		endX_ = startX + nTubes - 1;
		endY_ = startY;
	}
	if (direction == VERTICAL)
	{
		endX_ = startX;
		endY_ = startY + nTubes - 1;
	}
}
Ship::Ship(int startX, int startY, int endX, int endY): startX_(startX), startY_(startY), endX_(endX), endY_(endY)
{
}
int Ship::getStartX() const
{
	return startX_;
}
int Ship::getStartY() const
{
	return startY_;
}
int Ship::getEndX() const
{
	return endX_;
}
int Ship::getEndY() const
{
	return endY_;
}
void Ship::changeXY()
{
	startX_ += startY_;
	startY_ = startX_ - startY_;
	startX_ -= startY_;
	endX_ += endY_;
	endY_ = endX_ - endY_;
	endX_ -= endY_;
}

