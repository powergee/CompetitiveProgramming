#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);

        if ((y - x) % (a + b) == 0)
            printf("%d\n", (y - x) / (a + b));
        else printf("-1\n");
    }

    return 0;
}