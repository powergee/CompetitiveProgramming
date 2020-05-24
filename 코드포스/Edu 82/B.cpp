#include <iostream>

typedef long long Long;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        Long n, g, b;
        scanf("%lld %lld %lld", &n, &g, &b);

        Long good, badBtw;
        if ((n+1)/2 % g == 0)
        {
            good = ((n+1)/2 / g) * (g+b) - b;
            badBtw = ((n+1)/2 / g - 1) * b;
        }
        else 
        {
            good = ((n+1)/2 / g) * (g+b) + (n+1)/2 % g;
            badBtw = ((n+1)/2 / g) * b;
        }

        if (badBtw >= n/2)
            printf("%lld\n", good);
        else printf("%lld\n", good + (n/2 - badBtw));
    }

    return 0;
}