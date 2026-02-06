/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:12:06 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/06 12:08:46 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <climits>
#include <sys/time.h>

class PmergeMe{
	private:
		std::vector<int> _vector;
		std::deque<int>  _deque;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe operator=(const PmergeMe& other);
		~PmergeMe();

		void	parseInput(int argc, char** argv);
		void	sortAndDisplay();
	
	// Helper function for Jacobsthal sequence
	std::vector<size_t> generateJacobsthalOrder(size_t n);
	
	// Vector sorting methods
	std::vector<int> recursiveSortVec(std::vector<int>& container);
	std::vector<int> insertionPhaseVec(std::vector<int>& mainChain, 
			std::vector<std::pair<int, int> >& pairs, int struggler, bool hasStruggler);
	
	// Deque sorting methods
	std::deque<int> recursiveSortDeque(std::deque<int>& container);
	std::deque<int> insertionPhaseDeque(std::deque<int>& mainChain, 
			std::deque<std::pair<int, int> >& pairs, int struggler, bool hasStruggler);
};

#endif