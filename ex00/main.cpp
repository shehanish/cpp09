/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:20:07 by shkaruna          #+#    #+#             */
/*   Updated: 2025/12/01 14:40:27 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	BitcoinExchange  database;

	if(argc != 2)
	{
		std::cout << "Error: Not enough arguments: <Usage> <program name> <file name>" << std::endl;
		return(0);
	}
	
	std::string args = "data.csv";
	//todo - data.csv file open and save the data inside in to a database
	database.loadDatabase(args);
	//todo - print out an error if file open fail 
	//todo - 
	
	//std::cout << args << std::endl;
	

	// size_t pos = args.find(".csv");
	
	
	
		
	
	
	
		
	return(0);
}
