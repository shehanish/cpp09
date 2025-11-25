/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:20:45 by shkaruna          #+#    #+#             */
/*   Updated: 2025/11/25 19:20:53 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>

class BitcoinExchange 
{
	private:
		std::map<std::string, float> _database;
		
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange&  other);
		~BitcoinExchange();

		void loadDatabase(const std::string& filename);
};

