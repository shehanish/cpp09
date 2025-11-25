/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:20:28 by shkaruna          #+#    #+#             */
/*   Updated: 2025/11/25 19:20:53 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _database() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->_database = other._database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}


void	BitcoinExchange::loadDatabase(const std::string& filename)
{
	size_t pos = filename.find(".csv");
	
	if(pos != std::string::npos)
	{
		std::cout << "Correct argument format for argv[1]" << std::endl;
		std::ifstream file(filename.c_str());
		if(!file.is_open())
		{
			std::cerr << "Error: Fild couldn't open!" << std::endl;
		}
		else
		{
			std::string line;
			getline(file, line);
			
			
		}
	}
}