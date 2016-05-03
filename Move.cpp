#include "Move.h"

Move::Move(int x, int y) : moveX(x), moveY(y)
{
}
int Move::getMoveX() const
{
	return moveX;
}
int Move::getMoveY() const
{
	return moveY;
}
