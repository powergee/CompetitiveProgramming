#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>

int a, b, c;
std::vector<std::tuple<int, int, int>> def;

bool IsPossible(int count)
{
    std::vector<bool> select(7);
    std::fill(select.begin(), select.end() - count, false);
    std::fill(select.end() - count, select.end(), true);

    do
    {
        std::tuple<int, int, int> goal(0, 0, 0);
        for (int i = 0; i < 7; ++i)
        {
            if (select[i])
            {
                int a, b, c;
                std::tie(a, b, c) = goal;
                a += std::get<0>(def[i]);
                b += std::get<1>(def[i]);
                c += std::get<2>(def[i]);
                goal = {a, b ,c};
            }
        }

        int ga, gb, gc;
        std::tie(ga, gb, gc) = goal;
        if (ga <= a && gb <= b && gc <= c)
            return true;
    } while (std::next_permutation(select.begin(), select.end()));
    
    return false;
}

int main()
{
    def.push_back({1, 0, 0});
    def.push_back({0, 1, 0});
    def.push_back({0, 0, 1});
    def.push_back({1, 1, 0});
    def.push_back({0, 1, 1});
    def.push_back({1, 0, 1});
    def.push_back({1, 1, 1});

    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d %d", &a, &b, &c);
        for (int i = 7; i >= 0; --i)
        {
            if (IsPossible(i))
            {
                printf("%d\n", i);
                break;
            }
        }
    }

    return 0;
}