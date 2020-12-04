#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>

typedef long long Long;

Long arr[200011], diff[200010], diffSum[200010];
int n;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%lld", &arr[i]);

        if (n == 2)
            printf("0\n");
        else
        {
            for (int i = 1; i < n; ++i)
            {
                diff[i] = abs(arr[i] - arr[i + 1]);
                diffSum[i] = diffSum[i - 1] + diff[i];
            }
            diffSum[n] = diffSum[n-1];

            Long answer = LLONG_MAX;
            for (int i = 1; i <= n; ++i)
            {
                if (i == 1)
                {
                    answer = std::min(answer, diffSum[n-1] - diffSum[1]);
                }
                else if (i == n)
                {
                    answer = std::min(answer, diffSum[i-2]);
                }
                answer = std::min(answer, (diffSum[i - 2]) + abs(arr[i - 1] - arr[i + 1]) + (diffSum[n - 1] - diffSum[i]));
            }

            printf("%lld\n", answer);
        }
    }

    return 0;
}