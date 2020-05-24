#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

int main()
{
    std::vector<int> cows;
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int pos;
        scanf("%d", &pos);
        cows.push_back(pos);
    }

    std::sort(cows.begin(), cows.end());

    int maxResult, minResult = INT32_MAX;
    maxResult = std::max(cows[n - 2] - cows[0], cows[n - 1] - cows[1]) - (n - 2);

    if ((cows[n - 2] - cows[0] == n - 2 && cows[n - 1] - cows[n - 2] > 2) ||
        (cows[n - 1] - cows[1] == n - 2 && cows[1] - cows[0] > 2))
        minResult = 2;
    else
    {
        int right = 0;

        for (int left = 0; left < n; ++left)
        {
            while (right + 1 < n && cows[right + 1] - cows[left] <= n - 1)
                ++right;

            minResult = std::min(minResult, n - (right - left + 1));
        }
    }

    printf("%d\n%d", minResult, maxResult);

    return 0;
}