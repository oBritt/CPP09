

#include "BitcoinExchange.hpp"
#include <stdio.h>

int get_map(std::map<std::string, double>& mp)
{
    std::ifstream input;
    input.open("data.csv");
    if (!input.is_open())
    {
        std::cout << "error" << std::endl;
        return 0;
    }
    std::string line;
    std::getline(input, line);
    std::string key;
    double      val;
    std::string value;
    while (std::getline(input, line))
    {
        if (line == "")
        {
            continue;
        }
        int pos = line.find(",");
        key = line.substr(0, pos);
        value = line.substr(pos + 1, line.size());
        std::istringstream iss(value);
        iss >> val;
        mp[key] = val;
    }
    return (1);
}

int is_leap(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return true;
            return false;
        }
        return true;
    }
    return false;
}

int check_date(std::string date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
    {
        std::cout << "Error: date wrong format." << std::endl;
        return (0);
    }
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue ;
        if (!isdigit(date[i]))
        {
            std::cout << "Error: date must be numerical." << std::endl;
            return (0);
        }
    }
    int month;
    std::istringstream iss(date.substr(5, 2));
    iss >> month;
    if (month > 12 || month < 1)
    {
        std::cout << "Error: month is invalid." << std::endl;
        return (0);
    }
    int year;
    std::istringstream issss(date.substr(0, 4));
    issss >> year;
    int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (is_leap(year))
        months[1] = 29;
    
    int day;
    std::istringstream isss(date.substr(8, 2));
    isss >> day;
    if (day < 1 || months[month - 1] < day)
    {
        std::cout  << "Error: day is invalid." << std::endl;
        return (0);
    }
    return (1);
}

int check_value(std::string value)
{
    int i = 0;
    if (value[0] == '+' || value[0] == '-')
    {
        i++;
    }

    int seen = 0;
    while (i < value.size())
    {
        if (value[i] == '.')
        {
            if (seen)
            {
                std::cout << "Error: value must be int or float." << std::endl;
                return 0;
            }
            seen = 1;
        }
        else if (!isdigit(value[i]))
        {
            std::cout << "Error: value must be int or float." << std::endl;
            return (0);
        }
        i++;
    }
    double answer;
    std::istringstream iss(value);
    iss >> answer;
    if (answer < 0.0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return (0);
    }
    if (answer > 1000.0)
    {
        std::cout << "Error: too large a number." << std::endl;
        return (0);
    }
    return (1);
}

int amount_of_leaps(int year)
{
    int counter = 0;
    for (int i = 1; i < year - 1; i++)
    {
        if (is_leap(year))
            counter++;
    }
    return (counter);
}

int toInt(std::string str)
{
    int year;
    int month;
    int day;

    std::istringstream isss(str.substr(8, 2));
    isss >> day;
    std::istringstream issss(str.substr(0, 4));
    issss >> year;
    std::istringstream iss(str.substr(5, 2));
    iss >> month;
    int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int total = (year - 1) * 365;
    total += amount_of_leaps(year);
    for (int i = 0; i < month - 1; i++)
    {
        total += months[i];
    }
    total += day;
    if (is_leap(year) && month > 2)
        total++;
    return (total);
}

std::string get_best(std::string line, std::string prev, std::string cur)
{
    int l = toInt(line);
    int p = toInt(prev);
    int c = toInt(cur);
    if (l - p <= c - p)
        return (prev);
    return (cur);
}

std::pair<std::string, double> find_closest(std::map<std::string, double>& mp, std::string line)
{
    std::map<std::string, double>::iterator prev;
    std::map<std::string, double>::iterator t = mp.end();
    t--;
    for (std::map<std::string, double>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        if (it == mp.begin())
        {
            if (it->first >= line)
                return (std::make_pair(it->first, it->second));
        }
        else
        {
            if (line == it->first)
                return (std::make_pair(it->first, it->second));
            if (line > prev->first && line < it->first)
            {
                std::string fit = get_best(line, prev->first, it->first);
                return (std::make_pair(fit, mp[fit]));
            }
            if (it == t)
            {
                prev = it;
                break ;
            }
        }
        prev = it;
    }
    return (std::make_pair(prev->first, prev->second));
}

void handle_one_line(std::map<std::string, double>& mp, std::string line)
{
    if (line.find(" | ") == std::string::npos)
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return ;
    }
    int pos = line.find(" | ");
    std::string date = line.substr(0, pos);
    std::string value = line.substr(pos + 3, line.size() - pos - 3);
    if (!check_date(date))
        return ;
    if (!check_value(value))
        return ;
    double answer;
    std::istringstream iss(value);
    iss >> answer;
    std::pair<std::string, double> ind =  find_closest(mp, line);
    std::cout << ind.first << " => " << answer << " = " << answer * ind.second <<  std::endl; 
}