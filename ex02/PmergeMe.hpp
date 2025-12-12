/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:59:17 by ndogan            #+#    #+#             */
/*   Updated: 2025/09/25 18:09:19 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <deque>

bool isPositiveInteger(const std::string &s);
void fordJohnsonForVector(std::vector<int> &vec);
void printVector(std::vector<int> &c);
void printDeque(std::deque<int> &c);
void fordJohnsonForDeque(std::deque<int> &deq);
