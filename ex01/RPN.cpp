/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:58:28 by ndogan            #+#    #+#             */
/*   Updated: 2025/09/29 22:45:29 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stack>
#include <sstream>

static bool check_char(char c){
    if (isdigit(c))
        return 0;
    if (c == '*' || c == '/' || c == '+' || c == '-' )
        return 0;
    return 1;
}

static int check_values(std::string str, int &index){
    bool space = true;
    size_t s = 0;
    if (isspace(str[s]))
        s++;
    index = s;
    for (size_t i = s; i < str.length(); i++){
        if (isspace(str[i]))
        {
            if (space) return 1;
            space = true;
            continue;
        }
        else {
            if (space == false) return 1;
            space = false;
            if (check_char(str[i]))
                return 1;
        }
    }
    return 0;
}

int calculate(std::stack<int> &st, char sig){
    int first;
    int second;

    if (!st.empty())
        second = st.top();
    else
    {
        std::cerr << "Error: not enough value!" << std::endl;
        return 1;
    }
    st.pop();
    if (!st.empty())
        first = st.top();
    else
    {
        std::cerr << "Error: not enough value!" << std::endl;
        return 1;
    }
    st.pop();
    if (sig == '/'){
        if (second == 0)
        {
            std::cerr << "Error: the divisor cannot be zero!" << std::endl;
            return 1;
        }
        st.push(first / second);
    }
    else if (sig == '*')
        st.push(first * second);
    else if (sig == '-')
        st.push(first - second);
    else if (sig == '+')
        st.push(first + second);
    return 0;
}

int process(std::string argv){
    int index;
    if (argv.length() < 3)
    {
        std::cerr << "Error: Missing value!" << std::endl;
        return 1;
    }

    if (check_values(argv, index))
    {
        std::cerr << "Error: Invalid argument!" << std::endl;
        return 1;
    }
    std::stack<int> st;
    char c;

    for (size_t i = index; i < argv.length() ; i++)
    {
        c = argv[i];
        if (isspace(c))
            continue;
        if (isdigit(c))
            st.push(c - '0');
        else
            if (calculate(st, c))
                return 1;
    }
    if (st.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    int result = st.top();
    std::cout << result << std::endl;
    
    return 0;
}