
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "error" << std::endl;
        return 1;
    }
    std::map<std::string, double> mp;
    if (!get_map(mp))
        return 1;
    std::ifstream input;
    input.open(av[1]);
    if (!input.is_open())
    {
        std::cout << "error" << std::endl;
        return 1;
    }
    std::string line;
    std::getline(input, line);
    if (line != "date | value")
    {
        std::cout << "error" << std::endl;
        return 1;
    }
    while (std::getline(input, line))
    {
        handle_one_line(mp, line);
    }
}

