#include "ExtSortRange.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>

// initializa Chunk of Disk memory, each page in a group by itself
// create first empty page
ExtSortRange::ExtSortRange() : groupSize(1)
{
	Page* firstPage = new Page;
	pageRange.push_back(firstPage);
}

// delete all page from pageRange
ExtSortRange::~ExtSortRange() 
{
	while (!pageRange.empty()) {
		delete pageRange.back();
		pageRange.pop_back();
	}
}

// given unsorted input values, load them into pages
// create new page when necessary, and bookmark by pageRange vector
void ExtSortRange::load(std::string inputStr) 
{
	std::stringstream iss(inputStr);
	int input;
	while (iss >> input)
	{
		if (!pageRange.back()->load(input)) {
			Page* newPage = new Page;
			newPage->load(input);
			pageRange.push_back(newPage);
		}
	}
}

void ExtSortRange::print()
{
	for (auto page : pageRange) 
	{
		page->print();
	}
	std::cout << " |" << std::endl;
}

void ExtSortRange::extMergeSort()
{
	pass0Sort();
	std::cout << "-->pass 0" << std::endl;
	print();

	int passNum = 1;
	while (passMergeSort()) 
	{
		std::cout << "-->pass " << passNum++ << std::endl;
		print();
	}
	groupSize = 1; // reset groupSize for further sort
}


// TODO: implement pass 0 of external merge sort
// Hint: You may use method functions of Page class
void ExtSortRange::pass0Sort() 
{
	for (auto it = pageRange.begin(); it != pageRange.end(); ++it)
	{
		(*it)->sortPage();
	}
}

// TODO: implement one merge sort pass (not pass0) of external merge sort
// return false if no need to sort (actually do nothing)
// Hint: You may use member variable
bool ExtSortRange::passMergeSort() 
{
	int B1 = BUFFER_PAGE - 1;

	if ((groupSize / B1) >= pageRange.size())
	{
		return false;
	}
	else
	{
		groupSize = groupSize * B1;
		bool keep_sorting = true;
		int number_pages = int(pageRange.size());
		int sort_index = 0;
		while (keep_sorting)
		{
			//int keeper = 0;
			std::vector<int> inputData;
			for (int i = 0; i < groupSize; i++)
			{
				sort_index = sort_index + i;
				if (sort_index < number_pages)
				{
					std::vector<int> temp = pageRange[sort_index]->getData();
					delete pageRange[sort_index];
					pageRange[sort_index] = new Page;
					for (auto j : temp)
					{
						inputData.push_back(j);
					}
				}
				else
				{
					keep_sorting = false;
				}
			}
			std::sort(inputData.begin(), inputData.end());
			sort_index += 1;
			for (int i = 0; i < sort_index; i++)
			{
				for (auto k : inputData)
				{
					pageRange[i]->load(k);
				}
			}
		}
		return true;
	}
	
}
