#include <iostream>
#include <string>
#include <vector>

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
        int x;
        std::cin >> input >> x;
        std::vector<char> answer(input.size(), '1');

        for (int i = 0; i < (int)input.size(); ++i)
        {
            if (input[i] == '0')
            {
                if (i >= x)
                    answer[i-x] = '0';
                if (i+x < (int)input.size())
                    answer[i+x] = '0';
            }
        }

        bool success = true;
        for (int i = 0; i < (int)input.size() && success; ++i)
        {
            char current;
            if (x <= i && answer[i-x] == '1')
                current = '1';
            else if (i+x < (int)input.size() && answer[i+x] == '1')
                current = '1';
            else
                current = '0';

            if (current != input[i])
                success = false;
        }

        if (success)
        {
            answer.push_back(0);
            std::cout << &answer[0] << "\n";
        }
        else
            std::cout << "-1\n";
    }

    return 0;
}