#include <iostream>
#include <algorithm>

typedef long long Long;

Long L[1000000];
Long H[1000000];
Long dp[1000000];
int n, k, w;
const Long MOD = 1000000007;

int main()
{
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d: ", t);
        scanf("%d %d %d", &n, &k, &w);

        for (int i = 0; i < k; ++i)
            scanf("%lld", L+i);
        
        Long a, b, c, d;
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        for (int i = k; i < n; ++i)
            L[i] = (a*L[i-2] + b*L[i-1] + c) % d + 1;
        
        for (int i = 0; i < k; ++i)
            scanf("%lld", H+i);

        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        for (int i = k; i < n; ++i)
            H[i] = (a*H[i-2] + b*H[i-1] + c) % d + 1;

        std::fill(dp, dp+n, 0);
        dp[0] = (2*(w + H[0])) % MOD;

        for (int i = 1; i < n; ++i)
        {
            if (L[i-1]+w < L[i])
                dp[i] = dp[i-1] + 2*(w + H[i]);
            else
            {
                Long heightDiff = 1e9;
                int left = i;
                for (int j = i-1; j >= 0 && (L[j] <= L[i] && L[i] <= L[j]+w); --j)
                {
                    if (H[i]-H[j] < heightDiff)
                    {
                        heightDiff = std::max(H[i]-H[j], 0LL);
                        left = j;

                        if (heightDiff == 0)
                            break;
                    }
                }

                dp[i] = dp[left] + 2*(L[i]-L[left]+heightDiff);
            }

            dp[i] %= MOD;
            //printf("dp[%d]: %lld\n", i, dp[i]);
        }

        Long result = 1;
        for (int i = 0; i < n; ++i)
        {
            result *= dp[i];
            result %= MOD;
        }

        printf("%lld\n", result);
    }
}