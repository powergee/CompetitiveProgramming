#include <iostream>
#include <string>

int main()
{
    std::string word;
    std::cin >> word;

    bool isPalin = true;
    for (unsigned i = 0; isPalin && i < word.size() / 2; ++i)
        if (word[i] != word[word.size() - 1 - i])
            isPalin = false;

    std::cout << (isPalin ? 1 : 0);

    return 0;
}