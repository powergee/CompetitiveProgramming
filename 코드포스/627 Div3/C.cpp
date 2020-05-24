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
        std::string str;
        std::cin >> str;
        str += 'R';

        int prev = -1;
        int maxDist = 0;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == 'R')
            {
                maxDist = std::max(maxDist, i - prev);
                prev = i;
            }
        }

        std::cout << maxDist << "\n";
    }

    return 0;
}