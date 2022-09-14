#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line), line != "END")
    {
        std::reverse(line.begin(), line.end());
        std::cout << line << '\n';
    }
}