#include <iostream>
#include <string>
#include <tuple>

std::tuple<int, int, int> info[100];

std::pair<int, int> Judge(int n1, int n2)
{
    std::string s1 = std::to_string(n1), s2 = std::to_string(n2);
    int strike = 0, ball = 0;

    for (int i = 0; i < 3; ++i)
        if (s1[i] == s2[i])
            ++strike;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (i == j)
                continue;
            if (s1[i] == s2[j])
            {
                ++ball;
                break;
            }
        }
    }

    return { strike, ball };
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int query, strike, ball;
        scanf("%d %d %d", &query, &strike, &ball);
        info[i] = std::make_tuple(query, strike, ball);
    }

    int count = 0;

    for (int a = 1; a <= 9; ++a)
    {
        for (int b = 1; b <= 9; ++b)
        {
            for (int c = 1; c <= 9; ++c)
            {
                if (a == b || b == c || c == a)
                    continue;
                int i = a * 100 + b * 10 + c;

                bool valid = true;
                for (int j = 0; j < n && valid; ++j)
                {
                    int query, strike, ball;
                    std::tie(query, strike, ball) = info[j];
                    std::pair<int, int> jg = Judge(i, query);
                    if (jg.first != strike || jg.second != ball)
                        valid = false;
                }

                if (valid)
                    ++count;
            }
        }
    }

    printf("%d", count);

    return 0;
}