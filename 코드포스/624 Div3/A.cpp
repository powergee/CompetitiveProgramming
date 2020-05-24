#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        int c = b - a;
        if (c > 0)
        {
            if (c % 2)
                printf("1\n");
            else printf("2\n");
        }
        else if (c < 0)
        {
            if ((-c) % 2)
                printf("2\n");
            else printf("1\n");
        }
        else printf("0\n");
    }

    return 0;
}