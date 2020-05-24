#include <iostream>
#include <algorithm>
#include <cmath>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        int arr[200000];
        for (int i = 0; i < 2 * n; ++i)
            scanf("%d", arr + i);

        std::sort(arr, arr + 2 * n);
        printf("%d\n", abs(arr[n] - arr[n - 1]));
    }
}