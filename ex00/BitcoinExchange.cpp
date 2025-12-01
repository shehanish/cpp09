/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:20:28 by shkaruna          #+#    #+#             */
/*   Updated: 2025/12/01 17:52:48 by shkaruna         ###   ########.fr       */
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

void	trimWhiteSpace(const std::string& line)
{
	for(size_t i = 0; i < line.size() - 1; i++)
	{
		if(line[i] == ' ' || line[i] == '\r' || line[i] == '\n' || line[i] == '\t')
			i++;
		
	}
}

int		validateDateStr(std::string& dateStr)
{
		
}
std::string	extractDate(const std::string& line)
{
	size_t posComa = line.find(",");
	std::string dateStr;
	
	if(posComa != std::string::npos )
		dateStr = line.substr(0, posComa);
	else
		std::cout << "Error: Wrong file format!" << std::endl;
	validateDateStr(dateStr);
	return(dateStr);
}

std::string	extractValue(const std::string& line)
{
	size_t posComa = line.find(",");
	std::string value;
	
	if(posComa != std::string::npos )
		value  = line.substr(posComa + 1);
	else
		std::cout << "Error: Wrong file format!" << std::endl;
	
	return(value);
}

void	BitcoinExchange::loadDatabase(const std::string& filename)
{
	size_t pos = filename.find(".csv");
	
	if(pos != std::string::npos)
	{
		// Skip the CSV header line (first getline).
		// For each subsequent line:
		// Trim whitespace and strip trailing CR ('\r').
		// Find the first comma (,). Split into dateStr and valueStr.
		// Validate dateStr format (YYYY-MM-DD).
		// Convert valueStr to float safely (use strtof/strtod and check leftover characters).
		// Insert into the map: _database[dateStr] = value;
		//std::cout << "Correct argument format for argv[1]" << std::endl;
		std::ifstream file(filename.c_str());
		if(!file.is_open())
		{
			std::cerr << "Error: Fild couldn't open!" << std::endl;
			return;
		}
		else
		{
			std::string line;
			int lineNo = 1;
			while(getline(file, line))
			{
				trimWhiteSpace(line);
				extractDate(line);
				extractValue(line);
				//std::cout << line << std::endl;
				//_database[date] = value;
				lineNo++;
			}
		
			
			
			
			
		}
	}
	else
	{
		std::cout << "Error: Wrong input: <Usage> <program name> <file name>" << std::endl;
	}
}
