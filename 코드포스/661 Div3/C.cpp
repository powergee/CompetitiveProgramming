#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        int weights[51];
        bool considered[51];
        std::fill(weights, weights+51, 0);
        for (int i = 0; i < n; ++i)
        {
            int w;
            scanf("%d", &w);
            ++weights[w];
        }
        
        int result = 0;
        for (int s = 2; s <= 100; ++s)
        {
            int count = 0;
            std::fill(considered, considered+51, false);
            for (int i = 1; i <= n; ++i)
            {
                if (considered[i])
                    continue;
                
                int other = s - i;
                if (other <= 0 || other > n || considered[other])
                    continue;

                if (i == other)
                    count += weights[i]/2;
                else
                    count += std::min(weights[i], weights[other]);
                considered[i] = true;
                considered[other] = true;
            }
            result = std::max(count, result);
        }

        printf("%d\n", result);
    }

    return 0;
}