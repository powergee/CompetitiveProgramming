#include <iostream>
#include <algorithm>

int dp[50001];

int Count(int n)
{
    if (n == 0)
        return 0;

    int& result = dp[n];
    if (result != 1e9)
        return result;

    for (int i = 223; i >= 1; --i)
        if (i * i <= n)
            result = std::min(Count(n - i*i) + 1, result);

    return result;
}

int main()
{
    std::fill(dp, dp + 50001, 1e9);
    int n;
    std::cin >> n;
    std::cout << Count(n);

    return 0;
}