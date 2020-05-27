#include <iostream>
#include <algorithm>

int n;
int triangle[500][500];
int dp[500][500];

int GetMax(int r, int c)
{
    if (r >= n)
        return 0;
    
    int& result = dp[r][c];
    if (result != -1)
        return result;

    result = std::max(GetMax(r+1, c), GetMax(r+1, c+1)) + triangle[r][c];
    return result;
}

int main()
{
    scanf("%d", &n);
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < r + 1; ++c)
            scanf("%d", &triangle[r][c]);

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    printf("%d", GetMax(0, 0));

    return 0;
}