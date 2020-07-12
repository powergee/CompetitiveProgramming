#include <iostream>
#include <algorithm>

int arr[200000];
int n;

int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", arr+i);
        
        if (n == 1)
            printf("Case #%d: 1\n", t);
        else
        {
            int max = -1;
            int count = 0;
            for (int i = 0; i < n; ++i)
            {
                if (max < arr[i] && (i == n-1 || arr[i+1] < arr[i]))
                    ++count;
                max = std::max(max, arr[i]);
            }
            printf("Case #%d: %d\n", t, count);
        }
    }

    return 0;
}