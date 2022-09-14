#include <iostream>

int main()
{
    int n, k, arr[50];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", arr+i);
    scanf("%d", &k);

    for (int i = 0; i < n; ++i)
    {
        int maxPos = i;
        for (int j = i + 1; j < n && j - i <= k; ++j)
            if (arr[j] > arr[maxPos])
                maxPos = j;

        k -= (maxPos - i);
        for (int j = maxPos - 1; j >= i; --j)
            std::swap(arr[j], arr[j+1]);
    }

    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);

    return 0;
}