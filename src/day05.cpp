/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 05 - If You Give A Seed A Fertilizer             *    /.'.'.\
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
#include <climits>
#include <thread>
#include <atomic>

namespace Day05
{
	std::vector<uint64_t> seeds;

	struct map
	{
		uint64_t dest;
		uint64_t source;
		uint64_t len;
	};

	std::vector<map> seedToSoil;
	std::vector<map> soilToFertilizer;
	std::vector<map> fertilizerToWater;
	std::vector<map> waterToLight;
	std::vector<map> lightToTemp;
	std::vector<map> tempToHumidity;
	std::vector<map> humidityToLocation;

	static uint64_t CheckMapForNextDest(const std::vector<map>& m, uint64_t val)
	{
		uint64_t nextDest = 0;
		for(const map& record : m)
		{
			uint64_t min = record.source;
			uint64_t max = record.source + record.len;
			if (val >= min && val <= max)
			{
				// found it
				nextDest = val - record.source + record.dest;
				break;
			}
		}

		if (nextDest == 0)
		{
			return val;
		}
		return nextDest;
	}

	uint64_t SeedToLocation(const uint64_t& seed)
	{
		uint64_t lowestLoc = INT_MAX;
		// process each seed
		uint64_t soil = CheckMapForNextDest(seedToSoil, seed);
		uint64_t fertilizer = CheckMapForNextDest(soilToFertilizer, soil);
		uint64_t water = CheckMapForNextDest(fertilizerToWater, fertilizer);
		uint64_t light = CheckMapForNextDest(waterToLight, water);
		uint64_t temperature = CheckMapForNextDest(lightToTemp, light);
		uint64_t humidity = CheckMapForNextDest(tempToHumidity, temperature);
		uint64_t location = CheckMapForNextDest(humidityToLocation, humidity);

		return location;
	}

	void PartA(const std::vector<uint64_t>& p_seeds)
	{
		uint64_t lowestLoc = INT_MAX;
		for (uint64_t num : p_seeds)
		{
			// process each seed
			uint64_t location = SeedToLocation(num);

			if (location < lowestLoc)
				lowestLoc = location;
		}

		std::cout << "[Day 05] Part A: " << lowestLoc << std::endl;
	}

	std::atomic_uint64_t lowestLocPartB = INT_MAX;

	// threaded operation
	void RunSeedRange(uint64_t seed, int64_t len)
	{
		uint64_t lowestLocation = INT_MAX;
		while (len >= 0)
		{
			uint64_t location = SeedToLocation(seed);
			++seed;
			--len;

			if (location < lowestLocation)
				lowestLocation = location;
		}

		if (lowestLocation < lowestLocPartB)
			lowestLocPartB = lowestLocation;
	}

	void PartB(const std::vector<uint64_t>& p_seeds)
	{
		std::vector<std::thread> threads;
		for (int i = 0; i < p_seeds.size(); i+=2)
		{
			uint64_t seed = p_seeds[i];
			int64_t len = p_seeds[i+1];

			threads.push_back(std::thread(RunSeedRange,seed, len));
		}

		for (std::thread& t : threads)
			t.join();

		std::cout << "[Day 05] Part B: " << lowestLocPartB << std::endl;
	}


	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input05.txt", inputLines))
		{
			throw std::runtime_error("[Day 05] Unable to open input file.");
		}

		// line 0 is the seeds
		seeds = common::GetNumbersInString<uint64_t>(inputLines[0]);

		std::vector<map>* mapPtr = nullptr;
		for (int i = 1; i < inputLines.size(); ++i)
		{
			const std::string line = inputLines[i];

			if (line.empty())
			{
				continue;
			}
			else if (line == "seed-to-soil map:")
			{
				mapPtr = &seedToSoil;
			}
			else if (line == "soil-to-fertilizer map:")
			{
				mapPtr = &soilToFertilizer;
			}
			else if (line == "fertilizer-to-water map:")
			{
				mapPtr = &fertilizerToWater;
			}
			else if (line == "water-to-light map:")
			{
				mapPtr = &waterToLight;
			}
			else if (line == "light-to-temperature map:")
			{
				mapPtr = &lightToTemp;
			}
			else if (line == "temperature-to-humidity map:")
			{
				mapPtr = &tempToHumidity;
			}
			else if (line == "humidity-to-location map:")
			{
				mapPtr = &humidityToLocation;
			}
			else
			{
				if (!mapPtr)
				{
					throw std::runtime_error("Should not happen");
				}
				// load into current map
				std::vector<uint64_t> nums = std::move(common::GetNumbersInString<uint64_t>(line));
				(*mapPtr).push_back(map{nums[0], nums[1], nums[2]});
			}
		}

		PartA(seeds);
		PartB(seeds);
	}
}
