/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:24:27 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/02 12:13:16 by shkaruna         ###   ########.fr       */
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
	while(!_stack.empty()) _stack.pop();
		
	
	std::stringstream  ss(input);
	std::string 		token;
	int		operatorCount = 0;
		
	while(ss >> token)
	{
		
		if(isOperator(token))
		{
			operatorCount++;
			cCalculation(token);
		} else
		{
			if(token.size() != 1 || !std::isdigit(token[0]))
			{
				throw std::runtime_error("Only single digit numbers (0 - 9) are allowed!");
			}
			_stack.push(std::atof(token.c_str()));
		}
	}

	if (_stack.size() != 1 || operatorCount == 0)
	{
		throw std::runtime_error("Invalid Inputs.");
	}
	return _stack.top();
	
}

bool	RPN::isOperator(const std::string& token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

void	RPN::cCalculation(const std::string& op)
{
	if(_stack.size() < 2)
		throw std::runtime_error("Invalid Input: Not enough operands");
	
	double rnum = _stack.top(); _stack.pop(); //Right hand side number
	double lnum = _stack.top(); _stack.pop(); //Left hand side number
	
	if (op == "+") _stack.push(lnum + rnum);
	else if (op == "-") _stack.push(lnum - rnum);
	else if (op == "*") _stack.push(lnum * rnum);
	else if (op == "/"){
		if(rnum == 0) throw std::runtime_error("Division by zero.");
			_stack.push(lnum / rnum);
	}
		
}
//1. Read the input (Usually as a string or series of tokens)
//2. If the token us a number: push it onto the stack
//3. If the token is an operator:
	//Pop the top two numbers from the stack
	//Apply the operator (top1 + top2)
	//Push the result back onto the stack 
//4. Final result: after the input is exhisted, the only number on the stacj is the answer

