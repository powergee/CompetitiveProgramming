#include <iostream>
#define MOD 1000000007

typedef long long Long;

int n;
int arr[200001];
Long sum[200001];

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", arr+i);
        sum[i] = sum[i-1] + arr[i];
    }

    Long result = 0;
    for (int i = 1; i <= n; ++i)
    {
        result += (arr[i] % MOD) * (sum[i-1] % MOD);
        result %= MOD;
    }

    printf("%lld", result);

    return 0;
}