#include <iostream>

int main()
{
    int b, n, sum = 0;
    scanf("%d\n%d", &b, &n);

    for (int i = 0; i < n; ++i)
    {
        int val;
        scanf("%d", &val);
        sum += val;
        if (b - sum < 40)
        {
            printf("impossible");
            return 0;
        }
    }

    printf("possible");
    return 0;