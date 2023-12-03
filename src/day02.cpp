/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 02 - Cube Conundrum                              *    /.'.'.\
**                                                                              *   /'.''.'.\
**                                                                              *   ^^^[_]^^^
********************************************************************************/

#include "days.h"
#include "advent-common.h"
#include <iostream>
#include <string>
/*#include <vector>
#include <map>
#include <algorithm>*/

namespace Day02
{
	void PartA(const StringVector& inputLines)
	{
		uint32_t totalSum = 0;

		static constexpr const int MAX_RED 		= 12;
		static constexpr const int MAX_GREEN 	= 13;
		static constexpr const int MAX_BLUE 	= 14;

		for (int i = 0; i < inputLines.size(); ++i)
		{			
			int gameId = i + 1;
			bool possible = true;
			const std::string& line = inputLines[i];
			
			const StringVector idSplit = common::SplitStringWithDelimiter(line, ':');
			const StringVector games = common::SplitStringWithDelimiter(idSplit[1], ';');
			
			for (const std::string& game : games)
			{
				
				const StringVector hands = common::SplitStringWithDelimiter(game, ',');
				for (const std::string& hand : hands)
				{
					const uint32_t num = std::stoi(common::SplitStringWithDelimiter(hand.substr(1), ' ')[0]);
					const std::string color = common::SplitStringWithDelimiter(hand.substr(1), ' ')[1];
					if (color == "red" && num > MAX_RED)
					{
						possible = false;
					}
					else if (color == "green" && num > MAX_GREEN)
					{
						possible = false;
					}
					else if (color == "blue" && num > MAX_BLUE)
					{
						possible = false;
					}
				}
			}
			if (possible)
			{
				totalSum += gameId;
			}
		}
		
		std::cout << "[Day 02] Part A. Total sum is: " << totalSum << std::endl;
	}

	void PartB(const StringVector& inputLines)
	{
		uint32_t totalSum = 0;
		for (int i = 0; i < inputLines.size(); ++i)
		{
			const std::string& line = inputLines[i];
			
			const StringVector idSplit = common::SplitStringWithDelimiter(line, ':');
			const StringVector games = common::SplitStringWithDelimiter(idSplit[1], ';');

			uint32_t largestRed = 0, largestGreen = 0, largestBlue = 0;
			for (const std::string& game : games)
			{
				const StringVector hands = common::SplitStringWithDelimiter(game, ',');
				for (const std::string& hand : hands)
				{
					const uint32_t num = std::stoi(common::SplitStringWithDelimiter(hand.substr(1), ' ')[0]);
					const std::string color = common::SplitStringWithDelimiter(hand.substr(1), ' ')[1];
					if (color == "red")
					{
						largestRed = (num > largestRed) ? num : largestRed;
					}
					else if (color == "green")
					{
						largestGreen = (num > largestGreen) ? num : largestGreen;
					}
					else if (color == "blue")
					{
						largestBlue = (num > largestBlue) ? num : largestBlue;
					}
				}
			}
			totalSum += (largestRed * largestGreen * largestBlue);
		}

		std::cout << "[Day 02] Part B. Total sum is: " << totalSum << std::endl;
	}


	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input02.txt", inputLines))
		{
			throw std::runtime_error("[Day 02] Unable to open input file.");
		}
		PartA(inputLines);
		PartB(inputLines);
	}
}
