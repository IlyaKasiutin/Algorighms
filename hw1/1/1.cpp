/*
Если в числе содержится только один бит со значением 1, записать в выходной поток OK.
Иначе записать FAIL.
Необходимо использование битовых операций.
Использование арифметических операций запрещено.
*/


#include <iostream>

std::string solve(unsigned int value)
{
    unsigned int i = 1;
    while (i <= value && i <= 1 << 31)
    {
        if (i == value)
            return "OK";
        
        if (i != 1 << 31)
            i <<= 1;
        else
            break;
    }

    return "FAIL";
}

int main()
{
    unsigned int input = 0;
    std::cin >> input;

    std::cout << solve(input) << std::endl;
    return 0;
}