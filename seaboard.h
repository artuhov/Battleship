#pragma once

class seaboard
{
private:
	static const int board_size = 12;
	int board[board_size][board_size];
	bool chek_ship(int begin_x, int begin_y, int end_x, int end_y) const;
	void insert_ship(int begin_x, int begin_y, int end_x, int end_y);

public:
	seaboard();
	enum  parametrsONboard { emptyCell, insertedShip, strickenShip, bossShot };
	void add_value_on_board(int move_x, int move_y, parametrsONboard value)
	{
		board[move_y][move_x] = static_cast<int> (value);
	}
	int return_value_on_board(int move_x, int move_y) const 
	{
		return board[move_y][move_x];
	}
	void show_board(bool shipShow) const;
	void add_ships_manual();
	void add_ships_random();
	bool checking_kill_ship(int move_x, int move_y);
	void mark_kill_ship(int move_x, int move_y);
	bool winning_check();
};

