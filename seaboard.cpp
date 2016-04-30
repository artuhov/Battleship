#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include "seaboard.h"

bool seaboard::chek_ship(int begin_x, int begin_y, int end_x, int end_y) const
{
	if (begin_x > 10 || begin_y > 10 || end_x > 10 || end_y > 10 ||
		begin_x < 1 || begin_y < 1 || end_x < 1 || end_y < 1)		// error not on board or end of board
		return false;

	const int ship_size_round = 3;

	if (begin_y == end_y)  // the ship is positioned upright
	{
		int index = begin_x <= end_x ? begin_x : end_x;
		int sum = 0;
		for (int i = 0; i < ship_size_round; i++)
			for (int j = 0; j < abs(begin_x - end_x) + ship_size_round; j++)
				sum += board[begin_y - 1 + i][index - 1 + j];
		return sum == 0;
	}
	if (begin_x == end_x) // the ship is positioned horizontally
	{
		int index = begin_y < end_y ? begin_y : end_y;
		int sum = 0;
		for (int i = 0; i < abs(begin_y - end_y) + ship_size_round; i++)
			for (int j = 0; j < ship_size_round; j++)
				sum += board[index - 1 + i][begin_x - 1 + j];
		return sum == 0;
	}
	return false;
}

void seaboard::insert_ship(int begin_x, int begin_y, int end_x, int end_y)
{
	if (begin_x == end_x) // the ship is positioned upright or monotube ship
	{
		int index = begin_y <= end_y ? begin_y : end_y;
		for (int i = 0; i <= abs(begin_y - end_y); i++)
			board[index + i][begin_x] = 1;
	}
	if (begin_y == end_y)  // the ship is positioned horizontally
	{
		int index = begin_x < end_x ? begin_x : end_x;
		for (int i = 0; i <= abs(begin_x - end_x); i++)
			board[begin_y][index + i] = 1;
	}
}

seaboard::seaboard()
{
	for (int i = 0; i < board_size; i++)
		for (int j = 0; j < board_size; j++)
			board[i][j] = static_cast<int> (emptyCell);
}

void seaboard::show_board(bool shipShow) const
{
	std::cout << "  x|1 2 3 4 5 6 7 8 9 10\n";
	std::cout << " y_|____________________\n";

	for (int i = 1; i < board_size - 1; i++)
	{
		std::cout << std::setw(2) << i << " |";
		for (int j = 1; j < board_size - 1; j++)
			switch (board[i][j])
			{
			case emptyCell:
				std::cout << ". ";
				break;
			case insertedShip:
				if (shipShow)
					std::cout << static_cast <char>(-2) << " ";
				else
					std::cout << ". ";
				break;
			case strickenShip:
				std::cout << static_cast <char>(-8) << " ";
				break;
			case bossShot:
				std::cout << "x ";
				break;
			}
		std::cout << "| \n";
	}
	std::cout << "   |____________________|\n\n";
}

void seaboard::add_ships_manual()
{
	int begin_x;
	int begin_y;
	int end_x;
	int end_y;
	bool flag = true;

	this->seaboard::show_board(1);

	//Start enter Four-tube ship
	while (flag)
	{
		std::cout << "Enter Four-tube ship \n";
		std::cout << "Enter starting coordinates (x, y): ";
		std::cin >> begin_x >> begin_y;
		std::cout << std::endl;
		std::cout << "Enter end coordinates (x, y): ";
		std::cin >> end_x >> end_y;
		std::cout << std::endl;

		if (abs(begin_y - end_y) == 3 || abs(begin_x - end_x) == 3)
			if (seaboard::chek_ship(begin_x, begin_y, end_x, end_y))
			{
				seaboard::insert_ship(begin_x, begin_y, end_x, end_y);
				this->seaboard::show_board(1);
				flag = false;
			}
	}
	//End enter Four-tube ship

	int count = 0;

	//Start enter Triple-tube ships
	while (count < 2)
	{
		flag = true;
		while (flag)
		{
			std::cout << "Enter Triple-tube ships \n";
			std::cout << "You enter (" << count + 1 << ") ship from 2\n";
			std::cout << "Enter starting coordinates (x, y): ";
			std::cin >> begin_x >> begin_y;
			std::cout << std::endl;
			std::cout << "Enter end coordinates (x, y): ";
			std::cin >> end_x >> end_y;
			std::cout << std::endl;

			if (abs(begin_y - end_y) == 2 || abs(begin_x - end_x) == 2)

				if (seaboard::chek_ship(begin_x, begin_y, end_x, end_y))
				{
					seaboard::insert_ship(begin_x, begin_y, end_x, end_y);
					this->seaboard::show_board(1);
					flag = false;
					count++;
				}
		}
	}

	//End enter Triple-tube ships

	count = 0;

	//Start enter Twin-tube ships
	while (count < 3)
	{
		flag = true;
		while (flag)
		{
			std::cout << "Enter Twin-tube ships \n";
			std::cout << "You enter (" << count + 1 << ") ship from 3\n";
			std::cout << "Enter starting coordinates (x, y): ";
			std::cin >> begin_x >> begin_y;
			std::cout << std::endl;
			std::cout << "Enter end coordinates (x, y): ";
			std::cin >> end_x >> end_y;
			std::cout << std::endl;

			if (abs(begin_y - end_y) == 1 || abs(begin_x - end_x) == 1)

				if (seaboard::chek_ship(begin_x, begin_y, end_x, end_y))
				{
					seaboard::insert_ship(begin_x, begin_y, end_x, end_y);
					this->seaboard::show_board(1);
					flag = false;
					count++;
				}
		}
	}
	//End enter Twin-tube ships

	count = 0;

	//Start enter Monotube ships
	while (count < 4)
	{
		flag = true;
		while (flag)
		{
			std::cout << "Enter Monotube ships \n";
			std::cout << "You enter (" << count + 1 << ") ship from 4\n";
			std::cout << "Enter coordinates (x, y): ";
			std::cin >> begin_x >> begin_y;
			std::cout << std::endl;

			if (seaboard::chek_ship(begin_x, begin_y, begin_x, begin_y))
			{
				seaboard::insert_ship(begin_x, begin_y, begin_x, begin_y);
				this->seaboard::show_board(1);
				flag = false;
				count++;
			}
		}
	}
	//End enter Monotube ships
}

void seaboard::add_ships_random()
{
	int tubesONship = 4;
	int shipsize = 4;
	int numberOFships = 1;

	while (tubesONship)
	{
		for (int i = 0; i < numberOFships; i++)
		{
			bool flag = false;

			while (!flag)
			{
				int begin_x = 1 + rand() % 10;
				int begin_y = 1 + rand() % 10;
				int end_x = begin_x;
				int end_y = (begin_y + shipsize - 1 <= 10) ? (begin_y + shipsize - 1) : (begin_y - shipsize + 1);

				if (rand() % 2)		 // change begin_x with begin_y and etc for more random results
				{
					begin_x += begin_y;
					begin_y = begin_x - begin_y;
					begin_x -= begin_y;
					end_x += end_y;
					end_y = end_x - end_y;
					end_x -= end_y;
				}

				if (seaboard::chek_ship(begin_x, begin_y, end_x, end_y))
				{
					seaboard::insert_ship(begin_x, begin_y, end_x, end_y);
					flag = true;
				}
				else if (seaboard::chek_ship(begin_y, begin_x, end_y, end_x))
				{
					seaboard::insert_ship(begin_y, begin_x, end_y, end_x);
					flag = true;
				}
			}
		}
		numberOFships++;
		shipsize--;
		tubesONship--;
	}
}

bool seaboard::checking_kill_ship(int move_x, int move_y)
{
	int i = 0;
	//check upright coordinates to the downward
	while (board[move_y + i + 1][move_x] != emptyCell && board[move_y + i + 1][move_x] != bossShot)
	{
		if (board[move_y + i + 1][move_x] == insertedShip)
			return false;
		i++;
	}

	i = 0;
	//check upright coordinates to the upward
	while (board[move_y - i - 1][move_x] != emptyCell && board[move_y - i - 1][move_x] != bossShot)
	{
		if (board[move_y - i - 1][move_x] == insertedShip)
			return false;
		i++;
	}

	i = 0;
	//check horizontal coordinates to the rightward
	while (board[move_y][move_x + i + 1] != emptyCell && board[move_y][move_x + i + 1] != bossShot)
	{
		if (board[move_y][move_x + i + 1] == insertedShip)
			return false;
		i++;
	}

	i = 0;
	//check horizontal coordinates to the leftward
	while (board[move_y][move_x - i - 1] != emptyCell && board[move_y][move_x - i - 1] != bossShot)
	{
		if (board[move_y][move_x - i - 1] == insertedShip)
			return false;
		i++;
	}
	return true;
}

void seaboard::mark_kill_ship(int move_x, int move_y)
{
	int i;
	//mark horizontal coordinates to the rightward and leftward
	if (board[move_y][move_x + 1] != strickenShip && board[move_y][move_x - 1] != strickenShip)
	{
		i = 0;
		do {
			board[move_y + i][move_x + 1] = bossShot;
			board[move_y + i][move_x - 1] = bossShot;
		} while (board[move_y + i++][move_x] == strickenShip);
		board[move_y + i - 1][move_x] = bossShot;

		i = 0;
		do {
			board[move_y - i][move_x + 1] = bossShot;
			board[move_y - i][move_x - 1] = bossShot;
		} while (board[move_y - i++][move_x] == strickenShip);
		board[move_y - (i - 1)][move_x] = bossShot;
	}

	//mark upright coordinates to the upward and downward
	else
	{
		i = 0;
		do {
			board[move_y + 1][move_x + i] = bossShot;
			board[move_y - 1][move_x + i] = bossShot;
		} while (board[move_y][move_x + i++] == strickenShip);
		board[move_y][move_x + i - 1] = bossShot;

		i = 0;
		do {
			board[move_y + 1][move_x - i] = bossShot;
			board[move_y - 1][move_x - i] = bossShot;
		} while (board[move_y][move_x - i++] == strickenShip);
		board[move_y][move_x - (i - 1)] = bossShot;
	}
}

bool seaboard::winning_check()
{
	for (int i = 1; i < board_size - 1; i++)
		for (int j = 1; j < board_size - 1; j++)
			if (board[i][j] == insertedShip)
				return false;
	return true;
}