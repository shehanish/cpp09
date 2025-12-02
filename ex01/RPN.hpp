/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:24:45 by shkaruna          #+#    #+#             */
/*   Updated: 2025/12/02 16:40:59 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <stack>

class RPN 
{
	private:
		std::stack<int>  _stack;
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();
		
};