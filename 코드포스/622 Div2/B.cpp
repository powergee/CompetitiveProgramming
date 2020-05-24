#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        long long n, x, y;
        scanf("%lld %lld %lld", &n, &x, &y);

        if (x > y)
            std::swap(x, y);

        long long worst = y - x + 1;
        long long dist = std::min(n-y, x-1);
        worst += dist * 2;

        if (x - 1 > n - y)
            worst += x - 1 - n + y;

        std::vector<long long> best;
        best.push_back(0);
        if (x != 1)
            best.push_back(std::max(x - n + y, (long long)0));

        if (y != 1)
            best.push_back(std::max(y - n + x, (long long)0));

        printf("%lld ", *std::max_element(best.begin(), best.end()) + 1);
        printf("%lld\n", worst);
    }

    return 0;
}