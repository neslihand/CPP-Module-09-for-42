/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:34:46 by ndogan            #+#    #+#             */
/*   Updated: 2025/09/29 22:29:40 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: Not enought value!" << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> deq;

    for (int i = 1; i < argc; i++) {
        std::string s(argv[i]);
        if (!isPositiveInteger(s)) {
            std::cerr << "Error: Invalid Value!" << std::endl;
            return 1;
        }
        long n = std::atol(s.c_str());
        if (n <= 0 || n > 2147483647) {
            std::cerr << "Error: Value in invalid range!" << std::endl;
            return 1;
        }
        vec.push_back((int)(n));
        deq.push_back((int)(n));
    }

    std::cout << "Before: ";
    printVector(vec);

    clock_t startVec = clock();
    fordJohnsonForVector(vec);
    clock_t endVec = clock();

    clock_t startDeq = clock();
    fordJohnsonForDeque(deq);
    clock_t endDeq = clock();

    std::cout << "After: ";
    printDeque(deq);

    double timeVec = (double)(endVec - startVec) * 1000000.0 / CLOCKS_PER_SEC;
    double timeDeq = (double)(endDeq - startDeq) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;

    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque : " << timeDeq << " us" << std::endl;

    return 0;
}

