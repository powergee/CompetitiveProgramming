#include <iostream>
#include <cmath>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        double d;
        scanf("%d %lf", &n, &d);

        if (d <= n)
        {
            printf("YES\n");
            continue;
        }

        int ext = (int)sqrt(d) - 1;
        bool yes = false;

        for (int i = 0; !yes && i <= std::min(2*ext, n - 1); ++i)
            if (i + (int)ceil(d/(i+1)) <= n)
                yes = true;

        if (yes) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}