#include <iostream>
#include <string>
#include <algorithm>

bool set[21];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m;
    std::cin >> m;

    int x;
    while (m--)
    {
        std::string comm;
        std::cin >> comm;

        if (comm == "add")
        {
            std::cin >> x;
            set[x] = true;
        }
        else if (comm == "remove")
        {
            std::cin >> x;
            set[x] = false;
        }
        else if (comm == "check")
        {
            std::cin >> x;
            std::cout << (set[x] ? 1 : 0) << '\n';
        }
        else if (comm == "toggle")
        {
            std::cin >> x;
            set[x] = !set[x];
        }
        else if (comm == "all")
        {
            std::fill(set + 1, set + 21, true);
        }
        else if (comm == "empty")
        {
            std::fill(set + 1, set + 21, false);
        }
    }

    return 0;
}