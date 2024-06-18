

#include "RPN.hpp"


int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    try
    {
        std::cout << rpn(av[1]) << std::endl;
    }
    catch(std::exception& e)
    {
        std::cout << "Error" << std::endl;
    }
}