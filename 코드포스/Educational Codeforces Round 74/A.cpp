#include <iostream>
#include <cmath>

typedef long long Long;

int main()
{
    int N;
    scanf("%d", &N);

    while (N--)
    {
        Long x, y;
        scanf("%lld %lld", &x, &y);

        Long extra = x-y;
        Long sqrtExtra = sqrt(extra);
        Long smallest = 2;

        while (extra % smallest != 0 && sqrtExtra >= smallest)
            ++smallest;

        if (smallest < extra && extra % smallest == 0)
            printf("YES\n");

        else printf("NO\n");
    }

    return 0;
}