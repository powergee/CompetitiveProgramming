#include <iostream>

long long dp[101] {0, 1, 1, 1, 2, 2, };

long long P(int n)
{
    long long& result = dp[n];
    if (result != 0)
        return result;
    
    return result = P(n - 1) + P(n - 5);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        printf("%lld\n", P(n));
    }

    return 0;
}