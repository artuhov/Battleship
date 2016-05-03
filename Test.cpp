#include "Test.h"

int Test::incrementX = 0;
int Test::incrementY = 0;

int Test::getX() const
{
	return incrementX++ % 10 + 1;
}

int Test::getY() const
{
	return incrementY++ / 10 + 1;
}