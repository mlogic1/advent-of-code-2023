/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 08 - Haunted Wasteland                           *    /.'.'.\
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

namespace Day08
{
	void PartA(const StringVector& inputLines)
	{
		const std::string instructions = inputLines[0];

		std::map<std::string, std::pair<std::string, std::string>> networkMap;
		for (int i = 2; i < inputLines.size(); ++i)
		{
			StringVector split = common::SplitStringWithDelimiter(inputLines[i], '=');
			std::string key = split[0].substr(0, 3);
			std::string left = split[1].substr(2, 3);
			std::string right = split[1].substr(7, 3);
			networkMap.emplace(key, std::make_pair(left, right));
		}

		std::string currentPos = "AAA";
		uint32_t steps = 0;
		uint32_t curIndex = 0;
		while (currentPos != "ZZZ")
		{
			++steps;
			char currentInstr = instructions[curIndex];

			currentPos = (currentInstr == 'L') ? networkMap[currentPos].first : networkMap[currentPos].second;

			++curIndex;
			if (curIndex >= instructions.size())
				curIndex = 0;
		}
		std::cout << "[Day 08] Part A: " << steps << std::endl;
	}

	void PartB(const StringVector& inputLines)
	{
		const std::string instructions = inputLines[0];

		std::map<std::string, std::pair<std::string, std::string>> networkMap;

		std::vector<std::string> activeSearches;

		for (int i = 2; i < inputLines.size(); ++i)
		{
			StringVector split = common::SplitStringWithDelimiter(inputLines[i], '=');
			std::string key = split[0].substr(0, 3);
			std::string left = split[1].substr(2, 3);
			std::string right = split[1].substr(7, 3);
			networkMap.emplace(key, std::make_pair(left, right));

			if (key[2] == 'A')
			{
				activeSearches.push_back(key);
			}
		}

		uint64_t steps = 0;
		uint32_t curIndex = 0;
		bool allSearchesDone = false;
		do
		{
			++steps;
			char currentInstr = instructions[curIndex];
			bool allZ = true;
			for (std::string& pos : activeSearches)
			{
				pos = (currentInstr == 'L') ? networkMap[pos].first : networkMap[pos].second;

				if (pos[2] != 'Z')
					allZ = false;
			}

			++curIndex;
			if (curIndex >= instructions.size())
				curIndex = 0;


			if (steps % 100000 == 0)
				std::cout << "steps: " << steps << std::endl;

			if (allZ)
				allSearchesDone = true;
		} while (!allSearchesDone);


		std::cout << "[Day 08] Part B: " << 1337 << std::endl;
	}

	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input08.txt", inputLines))
		{
			throw std::runtime_error("[Day 08] Unable to open input file.");
		}

		PartA(inputLines);
		// PartB(inputLines); // part B does not work yet
	}
}
