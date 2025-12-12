/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:58:55 by ndogan            #+#    #+#             */
/*   Updated: 2025/09/29 22:52:51 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <map>
#include <sstream>

static int date_check(std::string date){
    if (date[4] != '-' || date[7] != '-')
        return 1;
    
    int year, month, day;
    std::stringstream ss(date);
    ss >> year >> month >> day;
    month *= -1;
    day *= -1;
    if (year < 1)
        return 1;
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return 1;
    if (month == 2){
        bool leap;
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            leap = true;
        else
            leap = false;

        if (leap && day > 29)
            return 1;
        if (!leap && day > 28)
            return 1;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return 1;
    }
    return 0;
}

static int get_data(std::map<std::string, double> &mp){
    std::ifstream data_file("data.csv");
    if (data_file.is_open()){
        std::string line;
        std::string date;
        float value;
        std::getline(data_file, line);
        while (std::getline(data_file, line)){
            if (line.length() < 12)
                continue;
            std::stringstream ss(line);
            std::getline(ss, date, ',');
            ss >> value;
            mp.insert(std::make_pair(date, value));
        }
       data_file.close(); 
    }
    else{
        std::cerr << "Error: could not open data file." << std::endl;
        return 1;
    }
    return 0;
}

static double get_value(std::map<std::string, double> mp, std::string date){
    std::map<std::string, double>::iterator itfirst = mp.begin();
    std::map<std::string, double>::iterator itlast = --mp.end();
    
    if (date < itfirst->first)
        return -1;
    if (date > itlast->first)
        return itlast->second;
    
    std::map<std::string, double>::iterator it = mp.upper_bound(date);
    --it;
    return it->second;
}

int open_and_read(std::string filename){
    std::ifstream input_file(filename.c_str());
    if (input_file.is_open()){
        std::string line;
        std::string date;
        std::map<std::string, double> mp;
        if (get_data(mp))
            return 1;
        double value = 0;
        std::getline(input_file, line);
        while (std::getline(input_file, line)){
            if (line.length() < 14){
                std::cout << "Error: bad input! => " << line << std::endl;
                continue;
            }
            if (line[10] != ' ' || line[12] != ' ' || line[11] != '|'){
                std::cout << "Error: bad input! => " << line << std::endl;
                continue;
            }
            std::stringstream ss(line);
            std::getline(ss, date, '|');
            ss >> value;
            if (date_check(date))
                std::cout << "Error: bad input => " << date << std::endl;
            else if (value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else if (value > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else
            {
                double result = get_value(mp, date);
                if (result == -1)
                    std::cout << "Error: date is too early (before available data)." << std::endl;
                else
                    std::cout << date << "=> " << value << " = " << result * value << std::endl;
            }
        }
        input_file.close();
    }
    else {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    return 0;
}