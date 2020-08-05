#include <iostream>
#include <climits>
#include <algorithm>

int a[50], b[50];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        int minA = INT32_MAX, minB = INT32_MAX;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", a+i);
            minA = std::min(minA, a[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", b+i);
            minB = std::min(minB, b[i]);
        }

        long long count = 0;  
        for (int i = 0; i < n; ++i)
            count += std::max(a[i] - minA, b[i] - minB);
        
        printf("%lld\n", count);
    }

    return 0;
}