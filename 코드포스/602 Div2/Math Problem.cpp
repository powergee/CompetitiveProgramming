#include <iostream>
#include <limits>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        int left = INT32_MAX, right = INT32_MIN;

        for (int i = 0; i < n; ++i)
        {
            int a, b;
            scanf("%d %d", &a, &b);

            left = std::min(left, b);
            right = std::max(right, a);
        }

        if (left > right)
            printf("0\n");
        else
            printf("%d\n", right - left);
    }
}