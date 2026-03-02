/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:12:03 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/06 12:08:46 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque)
{
	
}

PmergeMe PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<size_t> PmergeMe::generateJacobsthalOrder(size_t n)
{
	if (n == 0)
		return std::vector<size_t>();
	
	// Generate Jacobsthal numbers until we exceed n
	std::vector<size_t> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	
	while (true)
	{
		size_t next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		if (next >= n)
			break;
		jacobsthal.push_back(next);
	}
	
	// Build insertion order based on Jacobsthal sequence
	std::vector<size_t> order;
	
	// Start from index 1 (skip 0, as element at index 0 is inserted first automatically)
	for (size_t i = 2; i < jacobsthal.size(); ++i)
	{
		size_t current = jacobsthal[i];
		size_t previous = jacobsthal[i - 1];
		
		// Insert elements from current down to previous+1
		for (size_t j = current; j > previous && j <= n; --j)
		{
			order.push_back(j - 1); // -1 for 0-based indexing
		}
	}
	
	// Add any remaining elements not covered by Jacobsthal groups
	size_t lastJacob = jacobsthal.back();
	for (size_t i = lastJacob + 1; i <= n; ++i)
	{
		order.push_back(i - 1); // -1 for 0-based indexing
	}
	
	return order;
}

void	PmergeMe::parseInput(int argc, char** argv)
{
	for(int i = 1; i < argc; ++i)
	{
		std::string s(argv[i]);
		
		if(s.empty())
		{
			throw std::runtime_error("Error: empty argument");
		}
		
		if(s.find_first_not_of("0123456789") != std::string::npos)
		{
			throw std::runtime_error("Error: invalid input (only positive integers allowed)");
		}
		
		long val = std::atol(argv[i]);
		if(val > INT_MAX)
		{
			throw std::runtime_error("Error: number too large (exceeds INT_MAX)");
		}
		
		for(size_t j = 0; j < _vector.size(); ++j)
		{
			if(_vector[j] == val)
			{
				throw std::runtime_error("Error: duplicate value found");
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
		winners.push_back(pairs[i].first);
	
	std::vector<int> mainChain = recursiveSortVec(winners);
		
	return insertionPhaseVec(mainChain, pairs, struggler, hasStruggler);
}

std::vector<int> PmergeMe::insertionPhaseVec(std::vector<int>& mainChain, 
				std::vector<std::pair<int, int> >& pairs, int struggler, bool hasStruggler)
{
	// Step 1: Insert first loser (b1) at the beginning
	int	firstLoser = -1;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if(pairs[i].first == mainChain[0])
		{
			firstLoser = pairs[i].second;
			break;
		}
	}
	mainChain.insert(mainChain.begin(), firstLoser);

	// Step 2: Insert remaining losers using Jacobsthal insertion order
	std::vector<size_t> insertionOrder = generateJacobsthalOrder(pairs.size());
	
	for (size_t i = 0; i < insertionOrder.size(); ++i)
	{
		size_t pairIndex = insertionOrder[i];
		if (pairIndex >= pairs.size())
			continue;
		
		// Skip the first loser as it's already inserted
		if (pairs[pairIndex].second == firstLoser)
			continue;
		
		int loser = pairs[pairIndex].second;
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), loser);
		mainChain.insert(it, loser);
	}

	// Step 3: Insert struggler if exists
	if(hasStruggler)
	{
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), struggler);
		mainChain.insert(it, struggler);
	}
	
	return mainChain;
}

std::deque<int> PmergeMe::recursiveSortDeque(std::deque<int>& container)
{
	if(container.size() <= 1)
		return container;
	
	std::deque<std::pair<int, int> > pairs;
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

	std::deque<int> winners;
	for(size_t i = 0; i < pairs.size(); ++i)
		winners.push_back(pairs[i].first);
	
	std::deque<int> mainChain = recursiveSortDeque(winners);
		
	return insertionPhaseDeque(mainChain, pairs, struggler, hasStruggler);
}

std::deque<int> PmergeMe::insertionPhaseDeque(std::deque<int>& mainChain, 
				std::deque<std::pair<int, int> >& pairs, int struggler, bool hasStruggler)
{
	// Step 1: Insert first loser (b1) at the beginning
	int	firstLoser = -1;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if(pairs[i].first == mainChain[0])
		{
			firstLoser = pairs[i].second;
			break;
		}
	}
	mainChain.insert(mainChain.begin(), firstLoser);

	// Step 2: Insert remaining losers using Jacobsthal insertion order
	std::vector<size_t> insertionOrder = generateJacobsthalOrder(pairs.size());
	
	for (size_t i = 0; i < insertionOrder.size(); ++i)
	{
		size_t pairIndex = insertionOrder[i];
		if (pairIndex >= pairs.size())
			continue;
		
		// Skip the first loser as it's already inserted
		if (pairs[pairIndex].second == firstLoser)
			continue;
		
		int loser = pairs[pairIndex].second;
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), loser);
		mainChain.insert(it, loser);
	}

	// Step 3: Insert struggler if exists
	if(hasStruggler)
	{
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), struggler);
		mainChain.insert(it, struggler);
	}
	
	return mainChain;
}

void PmergeMe::sortAndDisplay()
{
	// Print "Before"
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size(); ++i)
	{
		if (i < 4)
		{
			std::cout << _vector[i] << " ";
		}
		else if (i == 4 && _vector.size() > 5)
		{
			std::cout << "[...]";
			break;
		}
		else if (_vector.size() <= 5)
		{
			std::cout << _vector[i];
			if (i < _vector.size() - 1)
				std::cout << " ";
		}
	}
	std::cout << std::endl;

	// Sort with vector and measure time
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::vector<int> vecCopy = _vector;
	std::vector<int> sortedVec = recursiveSortVec(vecCopy);
	gettimeofday(&end, NULL);
	double vecTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	// Sort with deque and measure time
	gettimeofday(&start, NULL);
	std::deque<int> dequeCopy = _deque;
	std::deque<int> sortedDeque = recursiveSortDeque(dequeCopy);
	gettimeofday(&end, NULL);
	double dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	// Print "After"
	std::cout << "After: ";
	for (size_t i = 0; i < sortedVec.size(); ++i)
	{
		if (i < 4)
		{
			std::cout << sortedVec[i] << " ";
		}
		else if (i == 4 && sortedVec.size() > 5)
		{
			std::cout << "[...]";
			break;
		}
		else if (sortedVec.size() <= 5)
		{
			std::cout << sortedVec[i];
			if (i < sortedVec.size() - 1)
				std::cout << " ";
		}
	}
	std::cout << std::endl;

	// Print timing information
	std::cout << "Time to process a range of " << _vector.size() 
	          << " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() 
	          << " elements with std::deque : " << dequeTime << " us" << std::endl;
}