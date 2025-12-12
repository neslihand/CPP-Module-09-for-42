/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:58:18 by ndogan            #+#    #+#             */
/*   Updated: 2025/09/23 18:58:20 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv){
    if (argc == 2)
    {
        if (process(argv[1]))
            return 1;
    }
    else{
        std::cerr << "Error: wrong argument count!" << std::endl;
    }
    return 0;
}