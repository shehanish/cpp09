/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:20:28 by shkaruna          #+#    #+#             */
/*   Updated: 2025/12/02 14:20:39 by shkaruna         ###   ########.fr       */
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

static std::string trim(const std::string& s)
{
	const char* whites = " \t\r\n";
	size_t start = s.find_first_not_of(whites);
	if (start == std::string::npos)
		return std::string();
	size_t end = s.find_last_not_of(whites);
	return s.substr(start, end - start + 1);
}


static bool parseFloat(const std::string& token, float& out)
{
	std::string t = trim(token);
	if (t.empty())
		return false;

	const char* str = t.c_str();
	char* end = NULL;
	errno = 0;
	double v = strtod(str, &end);

	if (end == str)
		return false;

	while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')
		++end;

	if (*end != '\0')
		return false;

	if (errno == ERANGE)
		return false;

	out = static_cast<float>(v);
	return true;
}


static bool isValidDate(const std::string& date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}
	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if (month == 2)
	{
		bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (leap ? 29 : 28))
			return false;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			return false;
	}

	return true;
}


void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;

	if (!std::getline(file, line))
	{
		std::cerr << "Error: database file is empty." << std::endl;
		return;
	}
	int lineNo = 1;
	while (std::getline(file, line))
	{
		lineNo++;

		line = trim(line);
		if (line.empty())
			continue;

		size_t pos = line.find(',');
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad format at line " << lineNo << std::endl;
			continue;
		}

		std::string dateStr  = trim(line.substr(0, pos));
		std::string valueStr = trim(line.substr(pos + 1));

		if (!isValidDate(dateStr))
		{
			std::cerr << "Error: bad date at line " << lineNo << " => " << dateStr << std::endl;
			continue;
		}
		
		float rate;
		if (!parseFloat(valueStr, rate))
		{
			std::cerr << "Error: bad rate at line " << lineNo << " => " << valueStr << std::endl;
			continue;
		}

		_database[dateStr] = rate;
	}

	file.close();
}

void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;

	if (!std::getline(file, line))
	{
		std::cerr << "Error: input file is empty." << std::endl;
		return;
	}

	while (std::getline(file, line))
	{
		line = trim(line);
		if (line.empty())
			continue;

		size_t pos = line.find('|');
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string dateStr  = trim(line.substr(0, pos));
		std::string valueStr = trim(line.substr(pos + 1));

		if (!isValidDate(dateStr))
		{
			std::cerr << "Error: bad input => " << dateStr << std::endl;
			continue;
		}

		float value;
		if (!parseFloat(valueStr, value))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		std::map<std::string, float>::iterator it = _database.lower_bound(dateStr);

		if (it == _database.end() || it->first != dateStr)
		{
			if (it == _database.begin())
			{
				std::cerr << "Error: date too early => " << dateStr << std::endl;
				continue;
			}
			--it;
		}
		float rate   = it->second;
		float result = value * rate;

		std::cout << dateStr << " => " << value << " = " << result << std::endl;
	}
	file.close();
}
