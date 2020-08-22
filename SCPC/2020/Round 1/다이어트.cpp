#include <iostream>
#include <algorithm>

int aFood[200000];
int bFood[200000];

int main()
{
    int T;
    scanf("%d", &T);

    for (int i = 1; i <= T; ++i)
    {
        printf("Case #%d\n", i);

        int n, k;
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; ++i)
            scanf("%d", aFood+i);
        for (int i = 0; i < n; ++i)
            scanf("%d", bFood+i);

        std::sort(aFood, aFood+n);
        std::sort(bFood, bFood+n);

        int max = 0;
        for (int i = 0; i < k; ++i)
            max = std::max(max, aFood[i]+bFood[k-1-i]);
        printf("%d\n", max);
    }
}