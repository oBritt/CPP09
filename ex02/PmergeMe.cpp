
#include "PmergeMe.hpp"


void get_pos_insert(int *arr, int size)
{
    int prev = 0;
    int current = 2;
    int powerOfTwo = 4;
    int stop = 0;
    int i = 0;
    int number = 0;
    int sum = 0;

    while (!stop)
    {
        number = current + sum;
        if (number > size)
        {
            stop = 1;
            number = size;
        }
        while (number > sum)
        {
            arr[i] = number;
            i++;
            number--;
        }
        sum += current;
        prev = current;
        current = powerOfTwo - prev;
        powerOfTwo *= 2;
    }
}

int find_pos_to_insert(int *arr, int element, int size)
{
    if (arr[0] > element)
    {
        return 0;
    }
    if (arr[size - 1] < element)
    {
        return (size);
    }
    int low = 0;
    int high = size - 1;
    while (1)
    {
        int middle = (low + high) / 2;
        if (arr[middle] > element)
        {
            high = middle - 1;
        }
        else
        {
            low = middle + 1;
        }
        if (!(high > low))
        {
            if (arr[high] > element)
                return (high);
            else
                return (high + 1);
        }
    }
}

void insertAtIndex(int *arr, int element, int size, int ind)
{
    for (int i = size - 1; i > ind; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[ind] = element;
}

int *func_ar(int *arr, int size)
{
    if (size == 1)
    {
        return arr;
    }
    else if (size == 2)
    {
        if (arr[0] > arr[1])
        {
            int temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        return (arr);
    }
    std::unordered_map<int, int> mp;
    int higher[size];
    int lower[size - (size / 2)];
    for (int i = 0; i < size / 2; i++)
    {
        if (arr[2 * i] > arr[2 * i + 1])
        {
            higher[i] = arr[2 * i]; 
            lower[i] = arr[2 * i + 1];
            mp.insert(std::make_pair(higher[i], lower[i]));
        }
        else
        {
            higher[i] = arr[2 * i + 1]; 
            lower[i] = arr[2 * i];
            mp.insert(std::make_pair(higher[i], lower[i]));
        }
    }
    if (size % 2)
    {
        lower[size / 2] = arr[size - 1];
    }
    func_ar(higher, size / 2);
    for (int i = 0; i < size / 2; i++)
    {
        lower[i] = mp.find(higher[i])->second;
    }

    int arrt[size - (size / 2) - 1];
    get_pos_insert(arrt, size - (size / 2) - 1);
    //  for (int i = 0; i < size - (size / 2) - 1; i++)
    // {
    //     std::cout << lower[i] << ": " << higher[i] << "      ";
    // } 
    // std::cout << std::endl;
    insertAtIndex(higher, lower[0], size, 0);
    // for (int i = 0; i < size - (size / 2) - 1; i++)
    // {
    //     std::cout << arrt[i] << ": " << lower[arrt[i]] << "      ";
    // } 
    // std::cout << std::endl;
    for (int i = 0; i < size - (size / 2) - 1; i++)
    {
        int pos = find_pos_to_insert(higher, lower[arrt[i]], size / 2 + 1 + i);
        insertAtIndex(higher, lower[arrt[i]], size, pos);
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = higher[i];
    }
    return arr;
}

int *func_lis(int *arr, int size)
{
    if (size == 1)
    {
        return arr;
    }
    else if (size == 2)
    {
        if (arr[0] > arr[1])
        {
            int temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        return (arr);
    }
    std::unordered_multimap<int, int> mp;
    int higher[size];
    int lower[size - (size / 2)];
    for (int i = 0; i < size / 2; i++)
    {
        if (arr[2 * i] > arr[2 * i + 1])
        {
            higher[i] = arr[2 * i]; 
            lower[i] = arr[2 * i + 1];
            mp.insert(std::make_pair(higher[i], lower[i]));
        }
        else
        {
            higher[i] = arr[2 * i + 1]; 
            lower[i] = arr[2 * i];
            mp.insert(std::make_pair(higher[i], lower[i]));
        }
    }
    if (size % 2)
    {
        lower[size / 2] = arr[size - 1];
    }
    func_ar(higher, size / 2);
    for (int i = 0; i < size / 2; i++)
    {
        lower[i] = mp.find(higher[i])->second;
    }

    int arrt[size - (size / 2) - 1];
    get_pos_insert(arrt, size - (size / 2) - 1);
    //  for (int i = 0; i < size - (size / 2) - 1; i++)
    // {
    //     std::cout << lower[i] << ": " << higher[i] << "      ";
    // } 
    // std::cout << std::endl;
    insertAtIndex(higher, lower[0], size, 0);
    // for (int i = 0; i < size - (size / 2) - 1; i++)
    // {
    //     std::cout << arrt[i] << ": " << lower[arrt[i]] << "      ";
    // } 
    // std::cout << std::endl;
    for (int i = 0; i < size - (size / 2) - 1; i++)
    {
        int pos = find_pos_to_insert(higher, lower[arrt[i]], size / 2 + 1 + i);
        insertAtIndex(higher, lower[arrt[i]], size, pos);
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = higher[i];
    }
    return arr;
}