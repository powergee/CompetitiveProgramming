#include <iostream>
#include <algorithm>

typedef long long Long;

void judge(Long ab, Long first, Long second)
{
    if (second > ab)
        printf("No\n");
    else
    {
        Long v = ab - second;
        Long c = ab;
        if (v + c < first)
            printf("No\n");
        else printf("Yes\n");
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        Long a, b, n, m;
        scanf("%lld %lld %lld %lld", &a, &b, &n, &m);

        if (a == b)
            judge(a, n, m);
        else if (a - b <= n && a > b)
            judge(b, n - (a-b), m);
        else if (b - a <= n && b > a)
            judge(a, n - (b-a), m);
        else if (std::min(a, b) >= m)
            printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}