#include <iostream>
#include <algorithm>

int main()
{
    int arr[100];
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    int maxSum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
                if (arr[i] + arr[j] + arr[k] <= m)
                    maxSum = std::max(maxSum, arr[i] + arr[j] + arr[k]);

    printf("%d", maxSum);

    return 0;
}