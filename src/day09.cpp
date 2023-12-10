/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 09 - Mirage Maintenance                          *    /.'.'.\
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

namespace Day09
{
	int32_t IterateSequences(std::vector<int32_t>& nums)
	{
		if (std::count(nums.begin(), nums.end(), 0) == nums.size())
			return 0;	// all zeroes

		std::vector<int32_t> diffs;
		for (int i = 1; i < nums.size(); ++i)
		{
			diffs.push_back(nums[i] - nums[i-1]);
		}
		int32_t inc = IterateSequences(diffs);
		nums.push_back(nums.back() + inc);
		return nums.back();
	}

	void PartAB(const StringVector& inputLines)
	{
		int64_t totalSumA = 0;
		int64_t totalSumB = 0;
		for (const std::string& line : inputLines)
		{
			std::vector<int32_t> nums;
			std::vector<int32_t> numsReversed;
			
			std::stringstream ss(line);
			int32_t num;
			while(ss >> num)
				nums.push_back(num);

			numsReversed = nums;
			std::reverse(numsReversed.begin(), numsReversed.end());

			int32_t resA = IterateSequences(nums);
			int32_t resB = IterateSequences(numsReversed);
			totalSumA += resA;
			totalSumB += resB;
		}
	
		std::cout << "[Day 09] Part A: " << totalSumA << std::endl;
		std::cout << "[Day 09] Part B: " << totalSumB << std::endl;
	}

	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input09.txt", inputLines))
		{
			throw std::runtime_error("[Day 09] Unable to open input file.");
		}

		// both days can easily be done at the same time
		PartAB(inputLines);
	}
}
