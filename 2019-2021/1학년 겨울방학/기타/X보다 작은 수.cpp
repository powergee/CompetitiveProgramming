#include <iostream>

int main()
{
    int n, x;
    scanf("%d %d", &n, &x);

    for (int i = 0; i < n; ++i)
    {
        int num;
        scanf("%d", &num);
        if (num < x)
            printf("%d ", num);
    }

    return 0;
}