#include <iostream>
#include <algorithm>

int goods[200001];
// priceMemo[i]: 처음부터 i 번째 인덱스까지 모두 구매할 수 있는 가장 싼 가격
int priceMemo[200001];
int n, p, k;

inline int ThreeMin(int a, int b, int c)
{
    return std::min(a, std::min(b, c));
}

// 위 memo 배열을 채우는 용도의 함수
int GetPrice(int last)
{
    if (last < 0)
        return 0;

    int& result = priceMemo[last];
    if (result != -1)
        return result;

    if (last - k + 1 >= 0)
        result = std::min(GetPrice(last - 1), GetPrice(last - k)) + goods[last];
    else result = GetPrice(last - 1) + goods[last];

    return result;
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
        std::fill(priceMemo, priceMemo + n, -1);
        priceMemo[0] = goods[0];
        GetPrice(n - 1);

        bool found = false;
        for (int i = n-1; i >= 0; --i)
        {
            if (priceMemo[i] <= p)
            {
                printf("%d\n", i + 1);
                found = true;
                break;
            }
        }

        if (!found)
            printf("0\n");
    }

    return 0;
}