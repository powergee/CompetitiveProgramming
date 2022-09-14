#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::unordered_map<int, std::string> numToStr;
    std::unordered_map<std::string, int> strToNum;
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        std::string name;
        std::cin >> name;

        numToStr[i] = name;
        strToNum[name] = i;
    }

    while (m--)
    {
        std::string input;
        std::cin >> input;

        if (isalpha(input[0]))
            std::cout << strToNum[input] << '\n';
        else std::cout << numToStr[std::stoi(input)] << '\n';
    }

    return 0;
}