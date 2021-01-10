#include <iostream>
#include <algorithm>

int n, m;
int rSum[101], bSum[101];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            int val;
            scanf("%d", &val);
            rSum[i] = rSum[i-1] + val;
        }

        scanf("%d", &m);
        for (int i = 1; i <= m; ++i)
        {
            int val;
            scanf("%d", &val);
            bSum[i] = bSum[i-1] + val;
        }

        int answer = 0;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                answer = std::max(answer, rSum[i] + bSum[j]);
        
        printf("%d\n", answer);
    }

    return 0;
}