#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        int count;

        if (n % 2 == 0)
        {
            count = n / 2;
        }
        else
        {
            putchar('7');
            count = (n - 3) / 2;
        }

        while (count--)
            putchar('1');
        putchar('\n');
    }

    return 0;
}