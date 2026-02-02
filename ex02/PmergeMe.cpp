/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:12:03 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/02 17:19:22 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Pmergeme.hpp>



void	PmergeMe::parseInput(int argc, char** argv)
{
	for(int i = 1; i < argc; ++i)
	{
		std::string s(argv[i]);
		
		if(s.empty() || s.find_first_not_of("0123456789") != std::string::npos)
		{
			throw std::runtime_error("Error: Invalid input - digits only!");
		}
		long val = std::atol(argv[i]);
		if(val > INT_MAX)
		{
			throw std::runtime_error("Error: Integer overflow.");
		}
		
		for(size_t j = 0; j < _vector.size(); ++j)
		{
			if(_vector[j] == val)
			{
				throw std::runtime_error("Error: Duplicate number found.");
			}
		}
		_vector.push_back(val);
		_deque.push_back(val);
	}
	
}

std::vector<int> PmergeMe::recursiveSortVec(std::vector<int>& container)
{
	if(container.size() <= 1)
		return container;
	
		std::vector<std::pair<int, int> > pairs;
		int struggler = -1;
		bool hasStruggler = (container.size() % 2 != 0);
		
		if (hasStruggler)
			struggler = container.back();
		
		for (size_t i = 0; i + 1 < container.size(); i += 2)
		{
			if(container[i] < container[i + 1])
				pairs.push_back(std::make_pair(container[i + 1], container[i]));
			else
				pairs.push_back(std::make_pair(container[i], container[i + 1]));
		}

		std::vector<int> winners;
		for(size_t i = 0; i < pairs.size(); ++i)
		{
			winners.push_back(pairs[i].first);
		}
		std::vector<int> mainChain = recursiveSortVec(winners);
		
		return insertionPhase(mainChain, pairs, struggler, hasStruggler);
}

std::vector<int> PmergeMe::insertionPhase(std::vector<int>& mainChain, 
				std::vector<std::pair<int, int> >& pairs, int struggler, bool hasStruggler)
{
	int	firstLoser = -1;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		
	}			
}