#pragma once

class Ship
{
public:
	enum TubesShip { FOURTUBE = 4, THREETUBE = 3, TWOTUBE = 2, MONOTUBE = 1 };
	Ship();
	Ship(TubesShip nTubes); // make random ship
	Ship(int startX, int startY, TubesShip nTubes, int direction); // make manual ship
	Ship(int startX, int startY, int endX, int endY);
	int getStartX() const;
	int getStartY() const;
	int getEndX() const;
	int getEndY() const;
	void changeXY();

private:
	int startX_;
	int startY_;
	int endX_;
	int endY_;
};