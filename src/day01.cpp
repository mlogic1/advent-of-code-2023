#include "days.h"
#include "advent-common.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace Day01
{
	void PartA(const StringVector& inputLines)
	{		
		uint64_t sum = 0;
		static const std::string NUMBERS = "123456789";
		for (const std::string& line : inputLines)
		{
			size_t posS = line.find_first_of(NUMBERS);
			size_t posE = line.find_last_of(NUMBERS);
			
			if ((posS == std::string::npos) || (posE == std::string::npos))
			{
				throw std::runtime_error("Unable to find both numbers in line: " + line);
			}

			int a = line[posS] - '0';
			int b = line[posE] - '0';
			sum += (a * 10) + b;
		}

		std::cout << "Part A: " << sum << std::endl;
	}

	void PartB(const StringVector& inputLines)
	{
		uint64_t sum = 0;
		static const std::map<std::string, int> VALUE_MAP_A = 
		{
			{ "one", 	1 },
			{ "two", 	2 },
			{ "three", 	3 },
			{ "four", 	4 },
			{ "five", 	5 },
			{ "six", 	6 },
			{ "seven",	7 },
			{ "eight", 	8 },
			{ "nine", 	9 }
		};

		static const std::map<size_t, std::string> VALUE_MAP_B = 
		{
			{ 	1 ,  "one"   },
			{ 	2 ,  "two"   },
			{ 	3 ,  "three" },
			{ 	4 ,  "four"  },
			{ 	5 ,  "five"  },
			{ 	6 ,  "six"   },
			{	7 ,  "seven" },
			{ 	8 ,  "eight" },
			{ 	9 ,  "nine"  }
		};

		static const std::vector<std::string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
		static const std::string NUMBERS = "123456789";

		for (const std::string& line : inputLines)
		{
			std::vector<std::pair<size_t, std::string>> findResults;

			for (const std::string& number : numbers)
			{
				size_t pos = line.find(number);
				
				while (pos != std::string::npos)
				{
					findResults.emplace_back( std::make_pair(pos, number) );
					pos = line.find(number, pos + 1);
				}
			}

			size_t posS = line.find_first_of(NUMBERS);
			size_t posE = line.find_last_of(NUMBERS);
			
			if (posS != std::string::npos)
			{
				findResults.emplace_back(std::make_pair(posS, VALUE_MAP_B.at( line[posS] - '0'  )));
			}

			if (posE != std::string::npos)
			{
				findResults.emplace_back(std::make_pair(posE, VALUE_MAP_B.at( line[posE] - '0'  )));
			}

			std::string smallest = (*std::min_element(findResults.begin(), findResults.end())).second;
			std::string largest = (*std::max_element(findResults.begin(), findResults.end())).second;

			int a = VALUE_MAP_A.at(smallest);
			int b = VALUE_MAP_A.at(largest);
			sum += (a * 10) + b;
		}

		std::cout << "Part B: " << sum << std::endl;
	}


	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input01.txt", inputLines))
		{
			throw std::runtime_error("[Day 01] Unable to open input file.");
		}
		PartA(inputLines);
		PartB(inputLines);
	}
}
