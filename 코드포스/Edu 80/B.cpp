#include <iostream>
#include <cmath>

typedef long long Long;

Long dp1[19], dp2[19];

Long Pow10(int exp)
{
    if (exp == 0)
        return 1;

    Long& result = dp1[exp];
    if (result != 0)
        return result;
    result = 1;

    return result = Pow10(exp - 1) * 10;
}

Long Get9Num(int len)
{
    if (len == 0)
        return 1;
    if (len == 1)
        return 9;

    Long& result = dp2[len];
    if (result != 0)
        return result;
    
    return result = 9 * Pow10(len - 1) + Get9Num(len - 1);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        Long A, B;
        scanf("%lld %lld", &A, &B);

        int bCount = 0;
        for (int i = 1;;++i)
        {
            if (Get9Num(i) <= B)
                ++bCount;
            else break;
        }

        printf("%lld\n", bCount * A);
    }

    return 0;
}