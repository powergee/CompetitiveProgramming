#include <iostream>

int coins[4] {25, 10, 5, 1};

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int extra;
        scanf("%d", &extra);

        for (int i = 0; i < 4; ++i)
        {
            int count = extra / coins[i];
            extra %= coins[i];

            printf("%d ", count);
        }
        printf("\n");
    }

    return 0;
}