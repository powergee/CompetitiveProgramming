#include <iostream>
#include <algorithm>

int n;
int arr[1002];

int GetQIndex()
{
    std::sort(arr, arr + n + 1);
    for (int i = n; i >= 0; --i)
    {
        int k = arr[i];
        int pCount = (n + 1) - i;

        if (pCount >= k)
        {
            for (int j = arr[i + 1] - 1; j > k; --j)
            {
                if (n - i >= j)
                    return j;
            }
            return k;
        }
    }

    return 0;
}

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%d", arr + i);
    arr[n + 1] = 10001;

    printf("%d", GetQIndex());

    return 0;
}