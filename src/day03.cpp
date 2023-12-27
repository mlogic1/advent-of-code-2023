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
#include <cstring>
#include <string>
#include <sstream>
#include <unordered_set>

namespace Day03
{
	bool CheckNeighbours(char** grid, int rows, int cols, int i, int j, int numLen)
	{
		static const char* SYM_LIST = "!\"#$%&'()*+,-/:;<=>?@";
		for (int c = j; c < j + numLen; ++c)
		{
			// top left
			if (i > 0 && c > 0)
			{
				if (grid[i - 1][c - 1] != '.')
				{
					return true;
				}
			}

			// top
			if (i > 0)
			{
                                if (std::strchr(SYM_LIST, grid[i - 1][c]) != nullptr)
                                {
					return true;
                                }
			}

			// top right
			if (i > 0 && c < cols - 1)
			{
				if (std::strchr(SYM_LIST, grid[i - 1][c + 1]) != nullptr)
                                {
                                        return true;
                                }
			}

			// left
			if (c > 0)
			{
                                if (std::strchr(SYM_LIST, grid[i][c - 1]) != nullptr)
                                {
					return true;
                                }
			}
			// right
			if (c < cols - 1)
			{
                                if (std::strchr(SYM_LIST, grid[i][c + 1]) != nullptr)
                                {
					return true;
                                }
			}

			// bottom left
			if (i < rows - 1 && c > 0)
			{
				if (std::strchr(SYM_LIST, grid[i + 1][c - 1]) != nullptr)
                                {
                                        return true;
                                }
			}

			// below
			if (i < rows - 1)
			{
                                if (std::strchr(SYM_LIST, grid[i + 1][c]) != nullptr)
                                {
					return true;
                                }
			}

			// bottom right
			if (i < rows - 1 && c < cols - 1)
			{
				if (std::strchr(SYM_LIST, grid[i + 1][c + 1]) != nullptr)
                                {
                                        return true;
                                }
			}
		}
		return false;
	}

	void PartA(const StringVector& inputLines)
	{
		const int rows = inputLines[0].size();
		const int cols = inputLines.size();
		char** grid = common::CreateGrid<char>(rows, cols);

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				grid[i][j] = inputLines[i][j];
			}
		}

		uint32_t currentRow = 0;
		uint32_t totalSum = 0;
		for (const std::string& row : inputLines)
		{
			std::stringstream ss(row);
			int num;
			while(!ss.eof())
			{
				char c;
				if (isdigit(ss.peek()))
				{
					ss >> num;
					std::string numStr = std::to_string(num);
					int index = static_cast<size_t>(ss.tellg()) - numStr.length();

					if (index < 0)	// correct index if tellg() returned -1
					{
						index = row.size() - numStr.length();
					}

					if (CheckNeighbours(grid, rows, cols, currentRow, index, numStr.length()))
					{
						totalSum += num;
					}
				}
				else
				{
					ss >> c;
				}
			}
			++currentRow;
		}

		common::DeleteGrid(grid, rows, cols);
		std::cout << "[Day 03] Part A: " << totalSum << std::endl;
	}

	std::unordered_set<uint32_t> find_neighbouring_integers(const std::vector<std::string>& matrix) {
	    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	    std::unordered_set<uint32_t> result;

	    for (int i = 0; i < matrix.size(); ++i) {
	        for (int j = 0; j < matrix[i].size(); ++j) {
	            if (matrix[i][j] == '*') {
	                for (int k = 0; k < 8; ++k) {
	                    int ni = i + dx[k], nj = j + dy[k];
	                    if (ni >= 0 && ni < matrix.size() && nj >= 0 && nj < matrix[i].size() && isdigit(matrix[ni][nj])) {
	                        // Move to the start of the integer
	                        while (nj > 0 && isdigit(matrix[ni][nj - 1])) {
	                            --nj;
	                        }
	                        // Now nj points to the start of the integer
	                        int start = nj;
	                        // Move to the end of the integer
	                        while (nj < matrix[i].size() && isdigit(matrix[ni][nj])) {
	                            ++nj;
	                        }
	                        // Now nj points to the position after the end of the integer
	                        std::string integer = matrix[ni].substr(start, nj - start);
	                        if (result.find(std::stoi(integer)) == result.end()) {
	                            // std::cout << integer << std::endl;
	                            result.insert(std::stoi(integer));
	                        }
	                    }
	                }
	            }
	        }
	    }

		return result;
	}

	void PartB(const StringVector& inputLines)
	{
		// find_neighbouring_integers(inputLines);

/*		const int rows = inputLines[0].size();
		const int cols = inputLines.size();
		char** grid = common::CreateGrid<char>(rows, cols);

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				grid[i][j] = inputLines[i][j];
			}
		}

		for (int i = 0; i < rows; ++i)
                {
                        for (int j = 0; j < cols; ++j)
                        {
				if (grid[i][j] == '*')
				{
				}
                        }
		}
*/
		int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
		int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            	std::unordered_set<uint32_t> result;

	            for (int i = 0; i < inputLines.size(); ++i) {
	                for (int j = 0; j < inputLines[i].size(); ++j) {
	                    if (inputLines[i][j] == '*')
		            {
	                        for (int k = 0; k < 8; ++k) {
	                            int ni = i + dx[k], nj = j + dy[k];
	                            if (ni >= 0 && ni < inputLines.size() && nj >= 0 && nj < inputLines[i].size() && isdigit(inputLines[ni][nj])) {
	                                // Move to the start of the integer
	                                while (nj > 0 && isdigit(inputLines[ni][nj - 1])) {
	                                    --nj;
	                                }
	                                // Now nj points to the start of the integer
	                                int start = nj;
	                                // Move to the end of the integer
	                                while (nj < inputLines[i].size() && isdigit(inputLines[ni][nj])) {
	                                    ++nj;
	                                }
	                                // Now nj points to the position after the end of the integer
	                                std::string integer = inputLines[ni].substr(start, nj - start);
	                                if (result.find(std::stoi(integer)) == result.end()) {
	                                    // std::cout << integer << std::endl;
	                                    result.insert(std::stoi(integer));
	                                }
	                            }
	                        }
				std::cout << "* found at: " << i << "\t" << j << ". Elements: ";
				for (uint32_t num : result)
					std::cout << num << "\t";
				std::cout << std::endl;
	                    }
	                }
	            }


		std::cout << "[Day 03] Part B: " << 1337 << std::endl;
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
