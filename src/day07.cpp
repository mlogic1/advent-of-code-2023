/************************  ADVENT OF CODE 2023 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                         Day 07 - Camel Cards                                 *    /.'.'.\
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
#include <unordered_set>
#include <ranges>

namespace Day07
{
	enum class HandType
	{
		HIGH_CARD = 0,
		ONE_PAIR,
		TWO_PAIR,
		THREE_OF_A_KIND,
		FULL_HOUSE,
		FOUR_OF_A_KIND,
		FIVE_OF_A_KIND
	};

	static const std::map<char, uint32_t> CARD_VAL
	{
		{ 'A', 14 },
		{ 'K', 13 },
		{ 'Q', 12 },
		{ 'J', 11 },
		{ 'T', 10 },
		{ '9', 9 },
		{ '8', 8 },
		{ '7', 7 },
		{ '6', 6 },
		{ '5', 5 },
		{ '4', 4 },
		{ '3', 3 },
		{ '2', 2 }
	};

	static const std::map<char, uint32_t> CARD_VAL_B
	{
		{ 'A', 14 },
		{ 'K', 13 },
		{ 'Q', 12 },
		{ 'T', 10 },
		{ '9', 9 },
		{ '8', 8 },
		{ '7', 7 },
		{ '6', 6 },
		{ '5', 5 },
		{ '4', 4 },
		{ '3', 3 },
		{ '2', 2 },
		{ 'J', 1 }
	};

	HandType CardsToType(const std::string& cards)
	{
		// Check five of a kind
		HandType result = HandType::HIGH_CARD;
		std::unordered_set<char> uniqueCards(cards.begin(), cards.end());
		for (char c : uniqueCards)
		{
			size_t charCount = std::count(cards.begin(), cards.end(), c);
			if (charCount <= 1)
				continue;

			if (charCount == 5)
			{
				result = HandType::FIVE_OF_A_KIND;
				break;
			}
			if (charCount == 4)
			{
				result = HandType::FOUR_OF_A_KIND;
				break;
			}

			if (charCount == 3)
			{
				if (result == HandType::ONE_PAIR)
				{
					result = HandType::FULL_HOUSE;
					break;
				}
				else
				{
					result = HandType::THREE_OF_A_KIND;
					continue;
				}
			}

			if (charCount == 2)
			{
				if (result == HandType::ONE_PAIR)
				{
					result = HandType::TWO_PAIR;
					break;
				}
				else if (result == HandType::THREE_OF_A_KIND)
				{
					result = HandType::FULL_HOUSE;
				}
				else
				{
					result = HandType::ONE_PAIR;
				}
			}
		}

		return result;
	}

	struct Hand
	{
		bool operator<(const Hand& other)
		{
			if (other.type == type)
			{
				for (int i = 0; i < cards.size(); ++i)
				{
					int t = CARD_VAL.at(cards[i]);
					int o = CARD_VAL.at(other.cards[i]);
					if (o > t)
					{
						return true;
					}
					else if (o < t)
					{
						return false;
					}
					else
					{
						if (i == 4){
							throw std::runtime_error("should not happen");
						}

						continue;
					}
				}
				// manually compare char by char
			}
			return other.type > type;
		}

		std::string cards;
		HandType type;
		uint32_t bid;
	};

	void PartA(const StringVector& inputLines)
	{
		std::vector<Hand> hands;
		for (const std::string& line : inputLines)
		{
			StringVector input = common::SplitStringWithDelimiter(line, ' ');
			Hand h{input[0], CardsToType(input[0]), static_cast<uint32_t>(std::stoul(input[1])) };

			hands.push_back(std::move(h));
		}

		// sort hands to determine rank
		std::sort(hands.begin(), hands.end());

		uint64_t totalWinnings = 0;
		for (int i = 0; i < hands.size(); ++i)
		{
			uint32_t rank = i + 1;
			totalWinnings += (hands[i].bid * rank);
		}
		std::cout << "[Day 07] Part A: " << totalWinnings << std::endl;
	}

	void PartB(const StringVector& inputLines)
	{
		std::vector<Hand> hands;
		for (const std::string& line : inputLines)
		{
			StringVector input = common::SplitStringWithDelimiter(line, ' ');
			Hand h{input[0], CardsToType(input[0]), static_cast<uint32_t>(std::stoul(input[1])) };

			hands.push_back(std::move(h));
		}

		// Before sorting to determine rank, all cards have to be checked for Jokers
		for (Hand& h : hands)
		{
			// not yet implemented
		}

		std::cout << "[Day 07] Part B: " << 0 << std::endl;
	}

	void RunDay()
	{
		StringVector inputLines;
		if (!common::ReadEntireFileStrings("input07.txt", inputLines))
		{
			throw std::runtime_error("[Day 07] Unable to open input file.");
		}

		PartA(inputLines);
		PartB(inputLines);	// part B does not work
	}
}
