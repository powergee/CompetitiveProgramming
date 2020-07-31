#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        if (n <= 30)
            printf("NO\n");
        else if (n == 36)
            printf("YES\n5 6 10 15\n");
        else if (n == 40)
            printf("YES\n10 14 15 1\n");
        else if (n == 44)
            printf("YES\n10 14 15 5\n");
        else
            printf("YES\n6 10 14 %d\n", n-30);
    }

    return 0;
}