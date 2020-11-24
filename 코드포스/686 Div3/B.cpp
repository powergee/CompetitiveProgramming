#include <iostream>
#include <algorithm>

std::pair<int, int> a[200000];

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &a[i].first);
            a[i].second = i+1;
        }
        
        std::sort(a, a+n);
        bool found = false;

        for (int i = 0; i < n && !found; ++i)
        {
            if (i == 0 && a[i].first != a[i+1].first)
            {
                printf("%d\n", a[i].second);
                found = true;
            }
            else if (i == n-1 && a[i-1].first != a[i].first)
            {
                printf("%d\n", a[i].second);
                found = true;
            }
            else if (a[i-1].first != a[i].first && a[i].first != a[i+1].first)
            {
                printf("%d\n", a[i].second);
                found = true;
            }
        }

        if (!found)
            printf("-1\n");
    }
    
    return 0;
}