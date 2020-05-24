#include <iostream>
#include <algorithm>

int c[200000];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", c + i);

    for (int i = 0; i < n; ++i)
    {
        int b;
        scanf("%d", &b);
        c[i] -= b;
    }

    std::sort(c, c + n);
    long long count = 0;

    for (int i = 0; i < n; ++i)
    {
        auto found = std::upper_bound(c + i + 1, c + n, -c[i]);
        count += (c + n) - found;
    }

    printf("%lld", count);

    return 0;
}