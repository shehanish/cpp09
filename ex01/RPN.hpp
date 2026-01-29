/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:24:45 by shkaruna          #+#    #+#             */
/*   Updated: 2026/01/29 14:27:19 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <stack>

class RPN 
{
	private:
		std::stack<double>  _stack;
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

