#include <iostream>
#include <algorithm>
#include <limits>

int n, k, l;
char str[10002];

int dp1[10001][10001];
int dp2[10001];

int main()
{
    scanf("%d %d %d", &n, &k, &l);
    scanf("%s", str + 1);

    for (int i = n; i >= 0; --i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (str[i] == str[j])
                dp1[i][j] = dp1[i + 1][j - 1] + 1;
            else
                dp1[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i)
        dp2[i] = 1e9;
    
    for (int i = 0; i < n; ++i)
    {
        if(dp2[i] < 1e9)
        {
            for (int j = i + 2; j <= n; ++j)
            {
                if (2 * dp1[i + 1][j] * l >= k * (j - i) && dp2[j] > dp2[i] + 1)
                    dp2[j] = dp2[i] + 1;
            }
        }
    }

    printf("%d", dp2[n] < 1e9 ? dp2[n] : 0);


    return 0;
}