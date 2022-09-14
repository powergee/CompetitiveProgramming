#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line), line[0] != '0')
    {
        bool isPalin = true;
        for (unsigned i = 0; isPalin && i < line.size() / 2; ++i)
            if (line[i] != line[line.size() - 1 - i])
                isPalin = false;
        
        std::cout << (isPalin ? "yes\n" : "no\n");
    }

    return 0;
}