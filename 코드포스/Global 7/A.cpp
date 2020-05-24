#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        if (n == 1)
            printf("-1\n");
        else
        {
            for (int i = 0; i < n - 2; ++i)
                putchar('7');
            printf("27\n");
        }
    }

    return 0;
}