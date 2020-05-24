#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        if (n % m == 0)
            printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}