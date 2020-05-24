#include <iostream>

int coins[10];

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
    {
        int input;
        scanf("%d", &input);
        coins[i] = input;
    }

    int count = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        while (k >= coins[i])
        {
            ++count;
            k -= coins[i];
        }

        if (k == 0)
            break;
    }

    printf("%d", count);

    return 0;
}