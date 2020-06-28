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
        std::string brStr;
        std::cin >> n >> brStr;

        int opening = 0;
        int answer = 0;
        for (int i = 0; i < n; ++i)
        {
            if (brStr[i] == '(')
                ++opening;
            else 
            {
                if (opening)
                    --opening;
                else
                    ++answer;
            }
        }

        std::cout << answer << '\n';
    }

    return 0;
}