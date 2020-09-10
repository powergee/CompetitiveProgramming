#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <functional>

int arr[1000];

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
        
        std::sort(arr, arr+n, std::greater<int>());
        int prevGcd = arr[0];
        for (int i = 1; i < n; ++i)
        {
            int maxGcd = 0;
            int maxIdx = 0;
            for (int j = i; j < n; ++j)
            {
                if (maxGcd < std::gcd(prevGcd, arr[j]))
                {
                    maxGcd = std::gcd(prevGcd, arr[j]);
                    maxIdx = j;
                }
            }

            std::swap(arr[i], arr[maxIdx]);
            prevGcd = std::gcd(prevGcd, maxGcd);
        }

        for (int i = 0; i < n; ++i)
            printf("%d ", arr[i]);
        printf("\n");
    }

    return 0;
}