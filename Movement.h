#pragma once
#include "Move.h"

class Movement
{
public:
	enum Direction { POSITIVE = 1, NEGATIVE = -1, NONE = 0 };
	Movement(int x, int y, Direction directX, Direction directY);
	Movement(Move obj, Direction directX, Direction directY);
	int getMovementX() const;
	int getMovementY() const;
	friend const Movement operator++(Movement& movement, int);

private:
	Move move;
	int increment;
	Direction directionX;
	Direction directionY;
};