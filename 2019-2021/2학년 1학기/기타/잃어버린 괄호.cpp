#include <iostream>
#include <string>
#include <sstream>

int SumAll(std::string s)
{
    std::stringstream ss(s);
    int result = 0;
    while (!ss.eof())
    {
        int val;
        ss >> val;
        result += abs(val);
    }
    return result;
}

int main()
{
    std::string exp;
    std::cin >> exp;

    size_t minus = exp.find('-');

    if (minus == std::string::npos)
        std::cout << SumAll(exp);
    else std::cout << SumAll(exp.substr(0, minus)) - SumAll(exp.substr(minus + 1));

    return 0;
}