#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, r;
        scanf("%d %d", &n, &r);

        long long alpha = std::min(n, r);

        if (n <= r)
        {
            printf("%lld\n", alpha * (alpha - 1) / 2 + 1);
        }
        else
        {
            printf("%lld\n", alpha * (alpha + 1) / 2);
        }
        
    }

    return 0;
}