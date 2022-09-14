#include <iostream>

typedef long long Long;
int n, k;

Long countSmaller(Long value)
{
    Long count = 0;
    for (int r = 1; r <= n; ++r)
    {
        int left = 0, right = n+1;
        while (left+1 < right)
        {
            int mid = (left + right) / 2;
            if ((Long)r*mid < value)
                left = mid;
            else
                right = mid;
        }

        count += left;
    }

    return count;
}

int main()
{
    scanf("%d%d", &n, &k);

    Long left = 1, right = (Long)n*n+1;
    while (left+1 < right)
    {
        Long mid = (left + right) / 2;
        if (countSmaller(mid) < k)
            left = mid;
        else
            right = mid;
    }

    printf("%lld", left);

    return 0;
}