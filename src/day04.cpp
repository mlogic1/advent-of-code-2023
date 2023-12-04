/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 04 - Scratchcards                                *    /.'.'.\
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

namespace Day04
{
	void PartA(const StringVector& inputLines)
	{
		uint32_t totalScore = 0;
		for (const std::string& line : inputLines)
		{
			const StringVector cardSplit = common::SplitStringWithDelimiter(line, ':');
			const StringVector numbers = common::SplitStringWithDelimiter(cardSplit[1], '|');
			std::vector<uint32_t> winningNums;
			std::vector<uint32_t> playerNums;
			std::stringstream ss(numbers[0]);
			uint32_t num;
			while (ss >> num)
				winningNums.push_back(num);

			ss = std::stringstream(numbers[1]);
			while(ss >> num)
				playerNums.push_back(num);

			int score = 0;
			for (uint32_t playerNumber : playerNums)
			{
				auto it = std::find(winningNums.begin(), winningNums.end(), playerNumber);
				if (it != winningNums.end())
				{
					score = (score == 0) ? 1 : score * 2;
				}
			}
			totalScore += score;
		}
		std::cout << "[Day 04] Part A: " << totalScore << std::endl;
	}

	static std::map<int, uint32_t> counts;	// finding all the results is very slow, that's the reason counts are cached

	static uint32_t countCopies(const StringVector& inputLines, int index)
	{
		if (counts.find(index) != counts.end())
			return counts.at(index);

		uint32_t count = 0;

		const std::string& line = inputLines[index];

		const StringVector cardSplit = common::SplitStringWithDelimiter(line, ':');
		const StringVector numbers = common::SplitStringWithDelimiter(cardSplit[1], '|');
		std::vector<uint32_t> winningNums;
		std::vector<uint32_t> playerNums;
		std::stringstream ss(numbers[0]);
		uint32_t num;
		while (ss >> num)
				winningNums.push_back(num);

		ss = std::stringstream(numbers[1]);
		while(ss >> num)
				playerNums.push_back(num);

		int subIndex = index;
		for (uint32_t playerNumber : playerNums)
		{
			auto it = std::find(winningNums.begin(), winningNums.end(), playerNumber);
			if (it != winningNums.end())
			{
				++subIndex;
				if (subIndex < inputLines.size())
					count += countCopies(inputLines, subIndex);
			}
		}

		counts.emplace(index, count + 1);
		return count + 1;
	}

	void PartB(const StringVector& inputLines)
	{
		uint32_t totalScore = 0;

		for (int i = 0; i < inputLines.size(); ++i)
		{
			const std::string& line = inputLines[i];
			totalScore += countCopies(inputLines, i);
		}

		std::cout << "[Day 04] Part B: " << totalScore << std::endl;
	}


	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input04.txt", inputLines))
		{
				throw std::runtime_error("[Day 04] Unable to open input file.");
		}
		PartA(inputLines);
		PartB(inputLines);
	}
}
