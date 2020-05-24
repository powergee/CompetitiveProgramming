#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>

bool selected[1000000];
std::string input;

std::tuple<int, int, int> GetPalin(int l, int r)
{
    if (r == l)
        return std::make_tuple(1, l, r);

    int n = r - l + 1;
    int length = 0;
    int i;
    for (i = l; i < n / 2; ++i)
    {
        if (input[l] != input[r])
            break;
        length += 2;
    }

    return std::make_tuple(length, i, r - (i - l));
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        std::cin >> input;

        int len, l, r;
        std::tie(len, l, r) = GetPalin(0, input.size() - 1);

        if (len == (int)input.size())
            std::cout << input;
        else
        {
            int newR = input.find_last_of(input[l], r);
            int newL = input.find(input[r], l);

            auto p1 = GetPalin(l, newR);
            auto p2 = GetPalin(newL, r);

            if (std::get<0>(p1) == newR - l + 1)
            {
                for (int i = 0; i <= newR; ++i)
                    std::cout << input[i];

                for (int i = r + 1; i < (int)input.size(); ++i)
                    std::cout << input[i];
            }
            else if (std::get<0>(p2) == l - newR + 1)
            {
                for (int i = 0; i < l; ++i)
                    std::cout << input[i];

                for (int i = newL; i < (int)input.size(); ++i)
                    std::cout << input[i];
            }
            else
            {
                if (l > 0)
                {
                    for (int i = 0; i < l; ++i)
                        std::cout << input[i];

                    for (int i = r + 1; i < (int)input.size(); ++i)
                        std::cout << input[i];
                }
                else std::cout << input[0];
            }
        }

        std::cout << '\n';
        
        std::fill(selected, selected + input.size(), false);
    }

    return 0;
}