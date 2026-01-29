/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:24:27 by shkaruna          #+#    #+#             */
/*   Updated: 2026/01/29 14:26:52 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {};

RPN::RPN(const RPN& other)
{
	*this = other;
}

RPN& RPN::operator=(const RPN& other)
{
	if(this != &other)
		this->_stack = other._stack;
	return *this;
}

RPN::~RPN() {};

double	RPN::myCalculator(const std::string& input)
{
	while(!_stack.empty())
		_stack.pop();
	
	
}

//1. Read the input (Usually as a string or series of tokens)
//2. If the token us a number: push it onto the stack
//3. If the token is an operator:
	//Pop the top two numbers from the stack
	//Apply the operator (top1 + top2)
	//Push the result back onto the stack 
//4. Final result: after the input is exhisted, the only number on the stacj is the answer

