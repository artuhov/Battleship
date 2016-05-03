#pragma once

class Move
{
public:
	Move(int x, int y);
	int getMoveX() const;
	int getMoveY() const;

private:
	int moveX;
	int moveY;
};