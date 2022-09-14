#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    int count = 0;
    bool appeared[26];
    std::string input;
    while (n--)
    {
        std::cin >> input;
        std::fill(appeared, appeared + 26, false);
        int i = 0;
        bool groupWord = true;
        while (i < (int)input.size())
        {
            if (appeared[input[i] - 'a'])
            {
                groupWord = false;
                break;
            }

            int last = i;
            while (last + 1 < (int)input.size() && input[i] == input[last + 1])
                ++last;

            i = last + 1;
            appeared[input[last] - 'a'] = true;
        }

        if (groupWord)
            ++count;
    }

    printf("%d", count);

    return 0;
}