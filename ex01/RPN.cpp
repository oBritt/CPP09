
#include "RPN.hpp"
#include <stdio.h>
// +-/*

void make_operation(std::stack<int>& s, int operation)
{
    if (s.size() < 2)
        throw std::exception();
    if (operation == 3 && s.top() == 0)
        throw std::exception();
    int first = s.top();
    s.pop();
    int second = s.top();
    s.pop();
    if (operation == 1)
        s.push(second + first);
    if (operation == 2)
        s.push(second - first);
    if (operation == 3)
        s.push(second / first);
    if (operation == 4)
        s.push(second * first);
}

bool is_numb(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

int rpn(std::string str)
{
    std::stack<int> s;
    int ptr1 = 0, ptr2 = 0;
    int stop = 0;
    while (!stop)
    {
        
        while (str[ptr1] == ' ')
        {
            ptr1++;
        }
        if (ptr1 == str.size())
            break ;
        ptr2 = str.substr(ptr1, str.size() - ptr1).find(" ");
        if (ptr2 == std::string::npos)
        {
            ptr2 = str.size() - ptr1;
            stop = 1;
        }
        std::string temp = str.substr(ptr1, ptr2);
        ptr1 += ptr2;
        if (is_numb(temp))
        {
            std::istringstream iss(temp);
            int num;
            iss >> num;
            s.push(num);
        }
        else if (temp == "+")
        {
            make_operation(s, 1);
        }
        else if (temp == "-")
        {
            make_operation(s, 2);
        }
        else if (temp == "/")
        {
            make_operation(s, 3);
        }
        else if (temp == "*")
        {
            make_operation(s, 4);
        }
        else
        {
            throw std::exception();
        }
    }
    if (s.size() != 1)
        throw std::exception();
    return (s.top());
}