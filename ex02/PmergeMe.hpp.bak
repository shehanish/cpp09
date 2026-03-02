/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmergeme.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:12:06 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/02 17:11:17 by shkaruna         ###   ########.fr       */
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
		std::vector<int> recursiveSortVec(std::vector<int>& container);
		std::vector<int> insertionPhase(std::vector<int>& mainChain, 
				std::vector<std::pair<int, int> >& pairs, int struggler, bool hasStruggler);
};

#endif