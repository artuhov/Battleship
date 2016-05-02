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
	startX_ = 1 + rand() % 10;
	startY_ = 1 + rand() % 10;
	endX_ = startX_;
	endY_ = (startY_ + nTubes - 1 <= 10) ? (startY_ + nTubes - 1) : (startY_ - nTubes + 1);

	if (rand() % 2)		 // change startX with startY and etc for more random results
		changeXY();
}
Ship::Ship(int startX, int startY, TubesShip nTubes, int direction)
{
	startX_ = startX;
	startY_ = startY;

	if (direction == 0)
	{
		endY_ = startY;
		endX_ = startX + nTubes - 1;
	}
	else
	{
		endY_ = startY + nTubes - 1;
		endX_ = startX;
	}

}
Ship::Ship(int startX, int startY, int endX, int endY)
{
	startX_ = startX;
	startY_ = startY;
	endX_ = endX;
	endY_ = endY;
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

