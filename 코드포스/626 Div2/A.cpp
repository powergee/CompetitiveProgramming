#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        int arr[101];
        scanf("%d", &n);

        int evenPos = -1;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", arr + i);
            if (arr[i] % 2 == 0)
                evenPos = i;
        }

        if (evenPos == -1)
        {
            if (n >= 2)
                printf("2\n1 2\n");
            else printf("-1\n");
        }
        else
        {
            printf("1\n%d\n", evenPos);
        }
    }

    return 0;
}