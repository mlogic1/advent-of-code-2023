/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 06 - Wait For It                                 *    /.'.'.\
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

namespace Day06
{
	void PartA(const StringVector& inputLines)
	{
		uint64_t totalNum = 1;
		std::vector<uint32_t> times 	= common::GetNumbersInString<uint32_t>(inputLines[0]);
		std::vector<uint32_t> distances = common::GetNumbersInString<uint32_t>(inputLines[1]);

		for (int i = 0; i < times.size(); ++i)
		{
			uint32_t time 				= times[i];
			uint32_t recordDistance 	= distances[i];
			uint32_t beatsRecordCount	= 0;

			for (int j = 0; j < time; ++j)
			{
				uint32_t speed = j;

				uint32_t distanceWithSpeed = speed * (time - j);
				if (distanceWithSpeed > recordDistance)
					++beatsRecordCount;
			}
			if (beatsRecordCount > 0)
			{
				totalNum *= beatsRecordCount;
			}
		}

		std::cout << "[Day 06] Part A: " << totalNum << std::endl;
	}

	void PartB(const StringVector& inputLines)
	{
		uint64_t totalNum = 0;

		std::vector<uint64_t> times 	= common::GetNumbersInString<uint64_t>(inputLines[0]);
		std::vector<uint64_t> distances = common::GetNumbersInString<uint64_t>(inputLines[1]);

		std::string timeStr{""};
		std::string distanceStr{""};
		for (int i = 0; i < times.size(); ++i)
		{
			timeStr 	+= std::to_string(times[i]);
			distanceStr += std::to_string(distances[i]);
		}

		uint64_t time = std::stoull(timeStr);
		uint64_t distance = std::stoull(distanceStr);

		for (int i = 0; i < time; ++i)
		{
			uint64_t speed = i;

			uint64_t distanceWithSpeed = speed * (time - i);
			if (distanceWithSpeed > distance)
				++totalNum;
		}


		std::cout << "[Day 06] Part B: " << totalNum << std::endl;
	}


	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input06.txt", inputLines))
		{
			throw std::runtime_error("[Day 06] Unable to open input file.");
		}

		PartA(inputLines);
		PartB(inputLines);
	}
}
