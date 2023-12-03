/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 03 - Gear Ratios                                 *    /.'.'.\
**                                                                              *   /'.''.'.\
**                                                                              *   ^^^[_]^^^
********************************************************************************/

#include "days.h"
#include "advent-common.h"
#include <iostream>
#include <string>

namespace Day03
{
	void PartA(const StringVector& inputLines)
	{
		int rows = inputLines[0].size();
		int cols = inputLines.size();
		char** grid = common::CreateGrid<char>(rows, cols);

		std::cout << rows << "\t" << cols << std::endl;

		common::DeleteGrid(grid, rows, cols);
	}

	void PartB(const StringVector& inputLines)
	{
		
	}


	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("sample.txt", inputLines))
		{
			throw std::runtime_error("[Day 03] Unable to open input file.");
		}
		PartA(inputLines);
		PartB(inputLines);
	}
}
