#include <iostream>
#include <algorithm>

int a[100];
bool able[100];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", a + i);
        }

        std::fill(able, able + n, false);
        for (int i = 0; i < m; ++i)
        {
            int pos;
            scanf("%d", &pos);
            able[pos - 1] = true;
        }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (able[j] && a[j] > a[j + 1])
                    std::swap(a[j], a[j + 1]);

        bool yes = true;
        for (int i = 0; i < n - 1; ++i)
        {
            if (a[i] > a[i + 1])
            {
                yes = false;
                break;
            }
        }

        if (yes)
            printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}