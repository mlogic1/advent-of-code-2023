/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 10 - Pipe Maze                                   *    /.'.'.\
**                                                                              *   /'.''.'.\
**                                                                              *   ^^^[_]^^^
********************************************************************************/

#include "days.h"
#include "advent-common.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

namespace Day10
{
	void PrintGrid(char** grid, int ii, int jj)
	{
		for (int i = 0; i < ii; ++i)
		{
			for (int j = 0; j < jj; ++j)
			{
				std::cout << grid[i][j];
			}
			std::cout << std::endl;
		}
	}

	enum class Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	std::tuple<int, int, Direction> DirToPos(char pipe, Direction dir, int posX, int posY)
	{
		if (dir == Direction::RIGHT)
		{
			switch (pipe)
			{
				case '-':
				{
					return std::tuple<int, int, Direction>(posX, posY + 1, dir);
					break;
				}

				case 'J':
				{
					return std::tuple<int, int, Direction>(posX - 1, posY, Direction::UP);
					break;
				}

				case '7':
				{
					return std::tuple<int, int, Direction>(posX + 1, posY, Direction::DOWN);
					break;
				}
			}
		}
		else if (dir == Direction::DOWN)
		{
			switch (pipe)
			{
				case '|':
				{
					return std::tuple<int, int, Direction>(posX + 1, posY, dir);
					break;
				}

				case 'J':
				{
					return std::tuple<int, int, Direction>(posX, posY - 1, Direction::LEFT);
					break;
				}

				case 'L':
				{
					return std::tuple<int, int, Direction>(posX, posY + 1, Direction::RIGHT);
					break;
				}
			}
		}
		else if (dir == Direction::LEFT)
		{
			switch (pipe)
			{
				case '-':
				{
					return std::tuple<int, int, Direction>(posX, posY - 1, dir);
					break;
				}

				case 'F':
				{
					return std::tuple<int, int, Direction>(posX + 1, posY, Direction::DOWN);
					break;
				}

				case 'L':
				{
					return std::tuple<int, int, Direction>(posX - 1, posY, Direction::UP);
					break;
				}
			}
		}
		else if (dir == Direction::UP)
		{
			switch (pipe)
			{
				case '|':
				{
					return std::tuple<int, int, Direction>(posX - 1, posY, dir);
					break;
				}

				case '7':
				{
					return std::tuple<int, int, Direction>(posX, posY - 1, Direction::LEFT);
					break;
				}

				case 'F':
				{
					return std::tuple<int, int, Direction>(posX, posY + 1, Direction::RIGHT);
					break;
				}
			}
		}
		throw std::runtime_error("Unable to determine path");
	}

	/* not good, this is not a good distance calculator */
	uint32_t IterPipes(char** grid, int posX, int posY, Direction d)
	{
		char c = grid[posX][posY];
		int nextX = -1, nextY = -1;
		uint32_t steps = 1337;
		std::tuple<int, int, Direction> next;
		switch (c)
		{
			case 'F':
			{
				next = DirToPos(c, d, posX, posY);
				break;
			}
			case '|':
			{
				next = DirToPos(c, d, posX, posY);
				break;
			}
			case '-':
			{
				next = DirToPos(c, d, posX, posY);
				break;
			}
			case '7':
			{
				next = DirToPos(c, d, posX, posY);
				break;
			}
			case 'J':
			{
				next = DirToPos(c, d, posX, posY);
				break;
			}
			case 'L':
			{
				next = DirToPos(c, d, posX, posY);
				break;
			}
			case 'S':
			{
				// made a full loop to start, no further steps required
				break;
			}
			default:
				throw std::runtime_error("unimplemented char");
				// Unknown character
				break;
		}

		nextX = std::get<0>(next);
		nextY = std::get<1>(next);
		Direction nextDir = std::get<2>(next);

		if (nextX == -1) // instead of this, check if next char is valid, return if not, otherwise iterate it
		{
			return steps;
		}
		
		uint32_t nextThing = IterPipes(grid, nextX, nextY, nextDir) + 1;

		return nextThing;
	}

	void PartA(const StringVector& inputLines)
	{
		const int rows = (int)inputLines.size();
		const int cols = (int)inputLines[0].length();
		char** grid = common::CreateGrid<char>(rows, cols);
		int startX, startY;

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				grid[i][j] = inputLines.at(i)[j];
				if (grid[i][j] == 'S')
				{
					startX = i;
					startY = j;
				}
			}
		}

		uint32_t stepsR = IterPipes(grid, startX, startY + 1, Direction::RIGHT);
		// uint32_t stepsD = IterPipes(grid, startX + 1, startY + 1, Direction::RIGHT);

		common::DeleteGrid<char>(grid, rows, cols);
		std::cout << "[Day 10] Part A: " << 1337 << std::endl;
	}

	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("sample.txt", inputLines))
		{
			throw std::runtime_error("[Day 10] Unable to open input file.");
		}

		PartA(inputLines);
	}
}
