#include <iostream>

int capacity[3];
int amount[3];

inline void Pour(int from, int to)
{
    int fromAmount, toAmount;

    if (amount[to] + amount[from] > capacity[to])
    {
        toAmount = capacity[to];
        fromAmount = amount[from] - (capacity[to] - amount[to]);
    }
    else
    {
        toAmount = amount[to] + amount[from];
        fromAmount = 0;
    }

    amount[from] = fromAmount;
    amount[to] = toAmount;
}

int main()
{
    for (int i = 0; i < 3; ++i)
        scanf("%d %d", capacity + i, amount + i);

    for (int i = 0; i < 100; ++i)
        Pour(i % 3, (i+1) % 3);

    for (int i = 0; i < 3; ++i)
        printf("%d\n", amount[i]);

    return 0;
}