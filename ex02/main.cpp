
#include "PmergeMe.hpp"

long long getCurrentTimeInMicroseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1e6 + ts.tv_nsec / 1000;
}
std::unordered_map<int, int> mp;
int check(std::string str, long long *arr, int e)
{
    
    int i = 0;    
    if (str[0] == '+')
        i = 1;
    while (i < str.size())
    {
        if (!isdigit(str[i]))
        {
            return (0);
        }
        i++;
    }
    long long n;
    std::istringstream iss(str);
    iss >> n;
    if (n > 2147483647)
    {
        return 0;
    }
    arr[e] = n;
    if (mp[n])
        return (0);
    mp[n] = 1;
    return (1);
}

void printtime(double time, int amount, std::string type)
{
    std::cout << "Time to process a range of ";
    if (amount < 1000)
        std::cout << " ";
    if (amount < 100)
        std::cout << " ";
    if (amount < 10)
        std::cout << " ";
    std::cout << amount << " elements with std:: " << type << " : " << time << " us" << std::endl;
}

double get_time_vector(int *arr, int size)
{
    std::clock_t start = std::clock();
    func_ar(arr, size);
    return static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * 100000;
}

double get_time_list(int *arr, int size)
{

    std::clock_t start_l = std::clock();
    func_lis(arr, size);
    return  static_cast<double>(std::clock() - start_l) / static_cast<double>(CLOCKS_PER_SEC) * 100000;
}

int main (int ac, char **av)
{
    if (ac == 1)
    {
        std::cout << "Error" << std::endl;
        return (1);
    }
    long long arr[ac];
    for (int i = 1; i < ac; i++)
    {
        std::string str = av[i];
        if (str.size() > 13)
        {
            std::cout << "Error" << std::endl;
            return (1);
        }
        if (!check(str, arr, i - 1))
        {
            std::cout << "Error" << std::endl;
            return (1);
        }
    }
    int arr1[ac];
    int arr2[ac];
    std::cout << "Before:   ";
    for (int i = 0; i < ac - 1; i++)
    {
        arr1[i] = arr[i];
        arr2[i] = arr[i];
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl << "After:    ";
    double time_taken_v = get_time_vector(arr1, ac - 1);
    double time_taken_l = get_time_list(arr2, ac - 1);

    for (int i = 0; i < ac - 1; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    printtime(time_taken_v, ac - 1, "unordered_map");
    printtime(time_taken_l, ac - 1, "unordered_mutlimap");
}