#include <iostream>
#include <algorithm>

int a[100], b[100];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", a + i);
        for (int i = 0; i < n; ++i)
            scanf("%d", b + i);

        std::sort(a, a + n);
        std::sort(b, b + n);
        for (int i = 0; i < n; ++i)
            printf("%d ", a[i]);
        printf("\n");
        for (int i = 0; i < n; ++i)
            printf("%d ", b[i]);
        printf("\n");
    }

    return 0;
}