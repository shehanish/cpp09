/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:11:59 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/02 16:23:54 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Pmergeme.hpp>


int 	main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cout << "Invalid input" << std::endl;
		return 1;
	}

	PmergeMe  solver;

	try
	{
		solver.parseInput(argc, argv);
		//Triger the sorting logic
		//solver.sortAndDisplay();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	return (0);
	
}