#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        int n;
        std::string str;
        std::cin >> n >> str;
        
        std::string smallest = str;
        int k = 1;

        for (int i = 2; i <= n; ++i)
        {
            std::string now = str.substr(i - 1);
            std::string tail = str.substr(0, i - 1);
            if ((n - i + 1) % 2 != 0)
                std::reverse(tail.begin(), tail.end());

            now += tail;
            if (smallest > now)
            {
                smallest = now;
                k = i;
            }
        }

        std::cout << smallest << "\n" << k << "\n";
    }
}