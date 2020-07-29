#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;
int arr[100001];
Long sum[100001];
int band[100000];
int maxBand[100000];
int n, k, z;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d %d", &n, &k, &z);

        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", arr+i);
            sum[i] = sum[i-1] + arr[i];
        }

        int currMax = 0;
        for (int i = 0; i <= n-1; ++i)
        {
            band[i] = arr[i]+arr[i+1];
            currMax = std::max(band[i], currMax);
            maxBand[i] = currMax;
        }

        Long answer = sum[k+1];
        for (int d = 1; d <= 2*z; ++d)
        {
            int end = k+1 - d;
            
            if (end < 2)
                break;

            if (d % 2 == 1)
                answer = std::max(answer, sum[end] + arr[end-1] + (Long)maxBand[end-1]*(d/2));
            else
                answer = std::max(answer, sum[end] + (Long)maxBand[end-1]*(d/2));
        }

        printf("%lld\n", answer);
    }
}