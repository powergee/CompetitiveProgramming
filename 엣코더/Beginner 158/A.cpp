#include <iostream>
#include <string>

int main()
{
    std::string str;
    std::cin >> str;

    bool same = true;
    for (int i = 0; i < 2 && same; ++i)
        if (str[i] != str[i + 1])
            same = false;

    std::cout << (same ? "No" : "Yes");
}