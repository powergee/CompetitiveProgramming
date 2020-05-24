#include <iostream>
#include <algorithm>
#include <limits>

int arr[100000];

bool Solve(int n)
{
    long long leftSum = 0, rightSum = 0;
    for (int i = 0; i < n; ++i)
    {
        leftSum += arr[i];
        if (leftSum <= 0)
            return false;
    }

    for (int i = n - 1; i >= 0; --i)
    {
        rightSum += arr[i];
        if (rightSum <= 0)
            return false;
    }

    return true;
}

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

        printf("%s\n", Solve(n) ? "YES" : "NO");
    }

    return 0;
}