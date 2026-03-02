/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:11:59 by shkaruna          #+#    #+#             */
/*   Updated: 2026/02/06 12:03:33 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: no arguments provided" << std::endl;
        return 1;
    }

    PmergeMe solver;
    try {
        solver.parseInput(argc, argv);
        solver.sortAndDisplay();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}