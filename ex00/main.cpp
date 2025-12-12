/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:58:46 by ndogan            #+#    #+#             */
/*   Updated: 2025/09/29 22:52:57 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv){
    if (argc == 2){
        if (open_and_read(argv[1]))
            return 1;
    }
    else
        std::cerr << "Error: could not open file." << std::endl;
    return 0;
}