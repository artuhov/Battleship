#include "Movement.h"


Movement::Movement(int x, int y, Direction directX, Direction directY): move(x,y), directionX(directX), directionY(directY), increment(1)
{
}
Movement::Movement(Move obj, Direction directX, Direction directY) : move(obj), directionX(directX), directionY(directY), increment(1)
{
}
int Movement::getMovementX()const
{
	return static_cast<int>(move.getMoveX() + directionX * increment);
}
int Movement::getMovementY() const
{
	return static_cast<int>(move.getMoveY() + directionY * increment);
}
const Movement operator++(Movement & movement, int)
{
	Movement oldMovement = movement;
	movement.increment++;
	return oldMovement;
}
