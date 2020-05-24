#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string line;
    std::cin >> line;

    for (int i = 0; i < line.size(); i += 10)
        std::cout << line.substr(i, 10) << '\n';

    return 0;
}