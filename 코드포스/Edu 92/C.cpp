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
        std::string input;
        std::cin >> input;

        int answer = (int)input.size();
        for (char i = '0'; i <= '9'; ++i)
        {
            for (char j = '0'; j <= '9'; ++j)
            {
                int current = 0;
                int matched = 0;
                bool turn = true;
                for (int k = 0; k < (int)input.size(); ++k)
                {
                    if (turn && input[k] == i)
                    {
                        turn = false;
                        ++matched;
                    }
                    else if (!turn && input[k] == j)
                    {
                        turn = true;
                        ++matched;
                    }
                    else
                        ++current;
                }

                if (i == j || matched % 2 == 0)
                    answer = std::min(answer, current);
            }
        }

        std::cout << answer << "\n";
    }

    return 0;
}