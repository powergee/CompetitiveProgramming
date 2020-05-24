#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string line;
    std::getline(std::cin, line);

    for (unsigned i = 0; i < line.size(); ++i)
    {
        char& ch = line[i];
        
        if ('a' <= ch && ch <= 'z')
            ch = (ch-'a' + 13) % 26 + 'a';
        else if ('A' <= ch && ch <= 'Z')
            ch = (ch-'A' + 13) % 26 + 'A';
    }

    std::cout << line;
}