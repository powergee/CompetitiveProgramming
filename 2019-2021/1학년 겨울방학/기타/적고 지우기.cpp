#include <iostream>
#include <algorithm>
#include <string>

bool written[10];

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        std::string input;
        std::cin >> input;

        std::fill(written, written + 10, false);
        for (char ch : input)
        {
            int index = (int)(ch - '0');
            written[index] = !written[index];
        }

        int answer = 0;
        for (int index = 0; index < 10; ++index)
            if (written[index])
                ++answer;

        std::cout << "#" << i << " " << answer << '\n';
    }

    return 0; 
}