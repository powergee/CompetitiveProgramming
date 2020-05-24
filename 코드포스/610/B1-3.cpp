#include <iostream>
#include <algorithm>

int goods[200001];
int maxCount = 0;
int n, p, k;

int Count(int wallet, int start, int bought)
{
    if (start >= n || wallet < 0)
        return 0;

    // 남은 제품을 다 사도 역대 최대 개수를 넘을 수 없을 때
    if (bought + (n - start) <= maxCount)
        return 0;

    if (maxCount == n)
        return 0;

    int currCount = 0;

    // start~(start+k-1)까지를 특별 구매하는 경우
    if (start <= n-k && wallet >= goods[start+k-1])
        currCount = std::max(currCount, Count(wallet - goods[start+k-1], start+k, bought+k) + k);

    // start를 그냥 구매하는 경우
    if (wallet >= goods[start])
        currCount = std::max(currCount, Count(wallet - goods[start], start+1, bought+1) + 1);

    maxCount = std::max(maxCount, currCount);
    return currCount;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d %d", &n, &p, &k);

        for (int i = 0; i < n; ++i)
            scanf("%d", goods + i);

        std::sort(goods, goods + n);

        maxCount = 0;
        Count(p, 0, 0);
        printf("%d\n", maxCount);
    }

    return 0;
}