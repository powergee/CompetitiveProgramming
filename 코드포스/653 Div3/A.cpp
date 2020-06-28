#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        long long x, y, n;
        scanf("%lld %lld %lld", &x, &y, &n);

        long long alpha = (n-y)/x;
        printf("%lld\n", x * alpha + y);
    }

    return 0;
}