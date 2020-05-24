#include <iostream>
#include <algorithm>
#include <functional>

int arr[100];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", arr + i);

        std::sort(arr, arr + n, std::greater<int>());
        for (int i = 0; i < n; ++i)
            printf("%d ", arr[i]);
        printf("\n");
    }

    return 0;
}