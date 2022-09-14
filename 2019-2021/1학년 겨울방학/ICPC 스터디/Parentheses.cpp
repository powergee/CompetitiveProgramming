#include <iostream>
#include <algorithm>
#include <string>

void PassBlank(const std::string& exp, int& pos)
{
    while (pos < exp.size() && isblank(exp[pos]))
        ++pos;
}

void PassWord(const std::string& exp, int& pos)
{
    while (pos < exp.size() && isalpha(exp[pos]))
        ++pos;
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string exp;
    std::cin >> exp;



    return 0;
}