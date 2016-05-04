#pragma once
#include "Board.h"
#include "BaseSetShips.h"
#include "ManualSetShips.h"
#include "RandomSetShips.h"

class GamePlay
{
public:
	bool setShipsPlayer();
	void setShipsComputer();
	void start();

private:
	enum  GameParametrs { GAMEOVER, SHIP_KILL, HIT_SHIP, MISS_FIRE, MISS };
	Board player;
	Board computer;
	GameParametrs makeMove(Board& board, int moveX, int moveY);
	GameParametrs finishShipKill(Board& board, int moveX, int moveY);
	void showGameBoards(bool showPlayerShip, bool showComputerShip);
};

