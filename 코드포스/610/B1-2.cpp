#include <iostream>
#include <algorithm>

int goods[200001];
int maxCount = 0;

int Count(int wallet, int k, int n, int bought)
{
    if (n <= 0 || wallet < 0)
        return 0;

    // 남은 제품을 다 사도 역대 최대 개수를 넘을 수 없을 때
    if (bought + n <= maxCount)
        return 0;

    int currCount = 0;

    // n-1 인덱스를 특별 구매하여 (n-k)~(n-1)까지를 구매하는 경우
    if (n-k >= 0 && wallet >= goods[n-1])
        currCount = std::max(currCount, Count(wallet - goods[n-1], k, n-k, bought + k) + k);

    // n-1 인덱스를 구매하는 경우
    if (wallet >= goods[n-1])
        currCount = std::max(currCount, Count(wallet - goods[n-1], k, n-1, bought + 1) + 1);

    // n-1 인덱스를 구매하지 않는 경우
    currCount = std::max(currCount, Count(wallet, k, n-1, bought));

    maxCount = std::max(maxCount, currCount);
    return currCount;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, p, k;
        scanf("%d %d %d", &n, &p, &k);

        for (int i = 0; i < n; ++i)
            scanf("%d", goods + i);

        std::sort(goods, goods + n);

        maxCount = 0;
        printf("%d\n", Count(p, k, n, 0));
    }

    return 0;
}