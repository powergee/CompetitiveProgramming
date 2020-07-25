#include <iostream>

typedef long long Long;

int main()
{
    int n;
    Long price[80];
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%lld", price+i);
    
    bool isIncreasing = price[0] <= price[1];
    Long currMoney = 1000;
    Long currStocks = 0;

    if (isIncreasing)
    {
        currStocks += currMoney / price[0];
        currMoney -= (currMoney / price[0]) * price[0];
    }

    for (int i = 1; i < n-1; ++i)
    {
        if (isIncreasing)
        {
            if (price[i] > price[i+1])
            {
                currMoney += currStocks * price[i];
                currStocks = 0;
                isIncreasing = false;
            }
        }
        else
        {
            if (price[i] <= price[i+1])
            {
                currStocks += currMoney / price[i];
                currMoney -= (currMoney / price[i]) * price[i];
                isIncreasing = true;
            }
        }
    }

    currMoney += currStocks * price[n-1];
    printf("%lld", currMoney);

    return 0;
}