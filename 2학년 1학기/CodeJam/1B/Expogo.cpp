#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

bool Contains(std::vector<int> vec, int val)
{
    auto it = std::lower_bound(vec.begin(), vec.end(), val);
    if (it == vec.end() || *it != val)
        return false;
    return true;
}

int GetLargest(int n)
{
    int count = 0;
    while (1 << (count + 1) <= n)
        ++count;
    
    return count;
}

std::vector<int> Factorize(int n)
{
    int exp = GetLargest(n);
    std::vector<int> result;

    while (n > 0)
    {
        while ((1 << exp) > n)
            --exp;
        result.push_back(exp);
        n -= 1 << exp;
    }

    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int c = 1; c <= T; ++c)
    {
        int x, y;
        scanf("%d%d", &x, &y);

        bool xEven = x % 2 == 0;
        bool yEven = y % 2 == 0;

        if (xEven == yEven)
            printf("Case #%d: %s\n", c, "IMPOSSIBLE");
        else
        {
            std::vector<int> xFactor, yFactor;

            if (xEven && x != 0)
            {
                xFactor = Factorize(abs(x));
                yFactor = Factorize(abs(y) + 1);
            }
            else if (yEven && y != 0)
            {
                xFactor = Factorize(abs(x) + 1);
                yFactor = Factorize(abs(y));
            }

            std::sort(xFactor.begin(), xFactor.end());
            std::sort(yFactor.begin(), yFactor.end());
            std::vector<int> common(xFactor.size() + yFactor.size());
            std::vector<int> uni(xFactor.size() + yFactor.size());
            auto it = std::set_intersection(xFactor.begin(), xFactor.end(),
                                            yFactor.begin(), yFactor.end(), common.begin());
            int comCount = it - common.begin();

            it = std::set_union(xFactor.begin(), xFactor.end(),
                                yFactor.begin(), yFactor.end(), uni.begin());

            bool noBlank = true;
            
            for (int i = 0; (i < it - uni.begin()) && noBlank; ++i)
                if (i != uni[i])
                    noBlank = false;

            if (comCount > 0 || !noBlank)
            {
                printf("Case #%d: %s\n", c, "IMPOSSIBLE");
            }
            else
            {
                printf("Case #%d: ", c);

                if (xEven)
                {
                    if (y > 0)
                        putchar('S');
                    else
                        putchar('N');
                }
                else
                {
                    if (x > 0)
                        putchar('W');
                    else
                        putchar('E');
                }

                for (int i = 0; i < it - uni.begin(); ++i)
                {
                    if (Contains(xFactor, i))
                    {
                        if (x > 0)
                            putchar('E');
                        else
                            putchar('W');
                    }
                    else
                    {
                        if (y > 0)
                            putchar('N');
                        else
                            putchar('S');
                    }
                }
                putchar('\n');
            }
        }
    }

    return 0;
}