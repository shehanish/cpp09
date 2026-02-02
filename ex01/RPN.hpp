/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:24:45 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/02 11:40:07 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>

class RPN 
{
	private:
		std::stack<double>  _stack;

		void	cCalculation(const std::string& op);
		bool	isOperator(const std::string& token);
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		double	myCalculator(const std::string& input);
		
};

//By adding std::stack<double>  _stack; you are telling 
//computer, everytime you call RPN myCal;, make sure 
//it has it's own dedicated bucket for numbers

