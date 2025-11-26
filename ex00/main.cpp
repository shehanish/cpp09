/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:20:07 by shkaruna          #+#    #+#             */
/*   Updated: 2025/11/26 10:32:25 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitcoinExchange  database;

	if(argc != 2)
	{
		std::cout << "Error: Wrong input: <Usage> <program name> <file name>" << std::endl;
		return(0);
	}
	
	std::string args = argv[1];
	//std::cout << args << std::endl;
	

	// size_t pos = args.find(".csv");
	
	database.loadDatabase(args);
	
		
	
	
	
		
	return(0);
}
