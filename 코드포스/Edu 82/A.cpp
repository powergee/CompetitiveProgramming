#include <iostream>
#include <string>

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        std::string input;
        std::cin >> input;

        int first = input.find_first_of('1');
        int last = input.find_last_of('1');

        if (first > last)
            printf("0\n");
        else
        {
            int result = 0;
            for (int i = first; i < last; ++i)
                if (input[i] == '0')
                    ++result;

            printf("%d\n", result);
        }
    }

    return 0;
}