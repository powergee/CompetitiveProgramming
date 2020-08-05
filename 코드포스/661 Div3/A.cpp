#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        int arr[50];
        for (int i = 0; i < n; ++i)
            scanf("%d", arr+i);
        
        std::sort(arr, arr+n);
        bool yes = true;
        for (int i = 0; i < n-1; ++i)
            if (arr[i+1] - arr[i] > 1)
                yes = false;
        
        printf("%s\n", yes ? "YES" : "NO");
    }

    return 0;
}