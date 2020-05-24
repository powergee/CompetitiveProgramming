#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string digit;
    std::cin >> digit;
    std::sort(digit.begin(), digit.end(), std::greater<char>());
    std::cout << digit;
}