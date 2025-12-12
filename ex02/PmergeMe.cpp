/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:57:15 by ndogan            #+#    #+#             */
/*   Updated: 2025/09/29 23:04:00 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>

bool isPositiveInteger(const std::string &s) {
    if (s.empty())
        return false;

    for (size_t i = 0; i < s.size(); i++) {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

void printVector(std::vector<int> &c) {
    if (c.size() > 5){
        std::vector<int>::iterator it = c.begin();
        for (int i = 0; i < 5; i++) {
            if (i == 4)
                std::cout << "[...]";
            else
                std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
        return;
    }
    for (std::vector<int>::iterator it = c.begin(); it != c.end(); ++it) {
            std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void printDeque(std::deque<int> &c) {
    if (c.size() > 5){
        std::deque<int>::iterator it = c.begin();
        for (int i = 0; i < 5; i++) {
            if (i == 4)
                std::cout << "[...]";
            else
                std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
        return;
    }
    for (std::deque<int>::iterator it = c.begin(); it != c.end(); ++it) {
            std::cout << *it << " ";
    }
    std::cout << std::endl;
}

std::deque<size_t> jacobsthalNumbersDeq(size_t n){
    std::deque<size_t> jacobs;

    if (n >= 1) jacobs.push_back(1);
    if (n >= 2) jacobs.push_back(3);
    
    for (size_t i = 2; jacobs.back() < n; ++i)
    {
        size_t next = jacobs[i - 1] + 2 * jacobs[i - 2];
        jacobs.push_back(next);
        if (next >= n) break;
    }

    return jacobs;
}

std::deque<int>::iterator binarySearchForDeque(int value,
    std::deque<int>::iterator begin,
    std::deque<int>::iterator end) {

    while (begin < end) {
        std::deque<int>::iterator mid = begin + (end - begin) / 2;

        if (*mid < value)
            begin = mid + 1;
        else
            end = mid;
    }
    return begin;
}


void fordJohnsonForDeque(std::deque<int> &deq){
    if (deq.size() <= 1) return;

    std::deque<int> winners;
    std::deque<int> losers;

    while (deq.size() >= 2)
    {
        int first = deq.front();
        deq.pop_front();
        int second = deq.front();
        deq.pop_front();

        if (first > second){
            winners.push_back(first);
            losers.push_back(second);
        }
        else{
            winners.push_back(second);
            losers.push_back(first);
        }
    }

    if(!deq.empty()){
        losers.push_back(deq.back());
        deq.pop_front();
    }

    fordJohnsonForDeque(winners);

    if (losers.empty())
    {
        deq.swap(winners);
        return;
    }

    std::deque<size_t> jacobs = jacobsthalNumbersDeq(losers.size());

    std::deque<int>::iterator insertPos = binarySearchForDeque(losers[0], winners.begin(), winners.end());

    winners.insert(insertPos, losers[0]);

    for (size_t i = 0; i < jacobs.size(); i++)
    {
        size_t jacobVal = jacobs[i];
        if (jacobVal >= losers.size()) break;

        size_t start = jacobVal;
        size_t end = (i + 1 < jacobs.size()) ? std::min(jacobs[i + 1], losers.size()) : losers.size();

        for (size_t j = start; j < end; ++j)
        {
            std::deque<int>::iterator pos = binarySearchForDeque(losers[j], winners.begin(),winners.end());
            winners.insert(pos, losers[j]);
        }
    }
    deq.swap(winners);
}


std::vector<size_t> jacobsthalNumbers(size_t n){
    std::vector<size_t> jacob;

    if (n >= 1) jacob.push_back(1);
    if (n >= 2) jacob.push_back(3);
    
    for (size_t i = 2; jacob.back() < n; ++i)
    {
        size_t next = jacob[i - 1] + 2 * jacob[i - 2];
        jacob.push_back(next);
        if (next >= n) break;
    }

    return jacob;
}

std::vector<int>::iterator binarySearchInVector(int value, std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    size_t low = 0;
    size_t high = end - begin;
    
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (*(begin + mid) < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return begin + low;
}

void fordJohnsonForVector(std::vector<int> &vec){
    if (vec.size() <= 1) return;

    std::vector<int> winners;
    std::vector<int> losers;

    const size_t size = vec.size();
    winners.reserve(size / 2);
    losers.reserve(size / 2 + 1);

    for (size_t i = 0; i + 1 < size; i += 2)
    {
        int first = vec[i];
        int second = vec[i + 1];

        if (first > second){
            winners.push_back(first);
            losers.push_back(second);
        }
        else{
            winners.push_back(second);
            losers.push_back(first);
        }
    }

    if (size % 2 != 0)
        losers.push_back(vec.back());

    fordJohnsonForVector(winners);

    if (losers.empty()){
        vec.swap(winners);
        return;
    }

    std::sort(losers.begin(), losers.end());

    std::vector<size_t> jacob = jacobsthalNumbers(losers.size());

    std::vector<int>::iterator pos = binarySearchInVector(losers[0], winners.begin(), winners.end());

    winners.insert(pos, losers[0]);
    
    for (size_t i = 0; i < jacob.size(); i++)
    {
        size_t start = jacob[i];
        size_t end = (i + 1 < jacob.size()) ? std::min(jacob[i + 1], losers.size()) : losers.size();

        for (size_t j = end; j > start; --j)
        {
            if (j - 1 < losers.size()){
                std::vector<int>::iterator insertPos = binarySearchInVector(losers[j - 1], winners.begin(), winners.end());
                winners.insert(insertPos, losers[j - 1]);
            }
        }
    }
    vec.swap(winners);    
}
