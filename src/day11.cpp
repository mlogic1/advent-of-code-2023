/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 11 - Cosmic Expansion                            *    /.'.'.\
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

namespace Day11
{
	void AddRow(std::vector< std::vector<bool> >& galaxyMap, int index)
	{
		const size_t cols = galaxyMap[0].size();
		std::vector<bool> emptyRow;
		for (size_t i = 0; i < cols; ++i)
		{
			emptyRow.push_back(false);
		}

		galaxyMap.insert(galaxyMap.begin() + index, emptyRow);
	}

	void AddColumn(std::vector< std::vector<bool> >& galaxyMap, int index)
	{
		for (std::vector<bool>& row : galaxyMap)
		{
			row.insert(row.begin() + index + 1, false); // make false
		}
	}

	void ExpandGalaxyMap(std::vector< std::vector<bool> >& galaxyMap)
	{
		IntVector newRows;
		IntVector newCols;

		const size_t rows = galaxyMap.size();
		const size_t cols = galaxyMap[0].size();
		// find empty rows
		for (size_t i = 0; i < rows; ++i)
		{
			if (std::count(galaxyMap[i].begin(), galaxyMap[i].end(), false) == galaxyMap[i].size())
			{
				std::cout << "Found row: " << i << std::endl;
				newRows.push_back(static_cast<int>(i));
			}
		}

		// find empty columns
		for (size_t j = 0; j < cols; ++j)
		{
			size_t count = 0;
			for (size_t i = 0; i< rows; ++i)
			{
				if (galaxyMap[i][j] == false)
					++count;
			}
			if (count == rows)
			{
				newCols.push_back(static_cast<int>(j));
				std::cout << "Detected col " << j << std::endl;
			}
		}

		for (int newRowIndex : newRows)
			AddRow(galaxyMap, newRowIndex);
		
		for (int newColIndex : newCols)
			AddColumn(galaxyMap, newColIndex);

	}

	void PartA(const StringVector& inputLines)
	{
		std::cout << "[Day 11] Part A: " << 1337 << std::endl;
		std::vector< std::vector<bool> > galaxyMap;
		for (int i = 0;i < inputLines.size(); ++i)
		{
			galaxyMap.push_back({});
			for (int j = 0;j < inputLines[i].length(); ++j)
			{
				galaxyMap.at(i).push_back( inputLines[i][j] == '#' );
			}
		}

		// expand the map
		ExpandGalaxyMap(galaxyMap);
		for (int i = 0; i < galaxyMap.size(); ++i)
		{
			for (int j = 0; j < galaxyMap[i].size(); ++j)
			{
				std::cout << galaxyMap[i][j];
			}
			std::cout << std::endl;
		}
	}

	void PartB(const StringVector& inputLines)
	{
		std::cout << "[Day 11] Part B: " << 1338 << std::endl;
	}

	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("sample.txt", inputLines))
		{
			throw std::runtime_error("[Day 11] Unable to open input file.");
		}

		PartA(inputLines);
	}
}
