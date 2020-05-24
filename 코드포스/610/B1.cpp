#include <iostream>
#include <algorithm>

int goods[200001];

// true : 범위 내 제품을 다 사고도 돈이 남음, false : 범위 내 제품을 다 사기 전에 돈이 바닥남.
inline bool TryToBuy(int start, int end, int& currCount, int& wallet)
{
    for (int j = start; j < end; ++j)
    {
        if (wallet >= goods[j])
        {
            wallet -= goods[j];
            ++currCount;
        }
        else 
            return false;
    }

    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        // 여기서 k는 항상 2
        int n, p, k;
        scanf("%d %d %d", &n, &p, &k);

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", goods + i);
        }

        std::sort(goods, goods + n);
        int maxCount = 0;
        int currCount = 0;
        int wallet;
        int pairPrice;

        // 정렬된 배열에서 i, i+1 원소를 특별 구입했다고 가정
        for (int i = 0; i < n - 1; ++i)
        {
            currCount = 0;
            wallet = p;
            pairPrice = goods[i + 1];
            if (wallet >= pairPrice)
            {
                wallet -= pairPrice;
                currCount += 2;

                // 구입한 2개보다 싼 제품을 구입하는 경우
                if (TryToBuy(0, i, currCount, wallet))
                    // 구입한 2개보다 비싼 제품을 구입하는 경우
                    TryToBuy(i + 2, n, currCount, wallet);

                maxCount = std::max(maxCount, currCount);
            }
            else break;
        }

        // 만약 특별 구입을 하지 않는다면?
        currCount = 0;
        wallet = p;

        TryToBuy(0, n, currCount, wallet);
        maxCount = std::max(maxCount, currCount);

        printf("%d\n", maxCount);
    }

    return 0;
}