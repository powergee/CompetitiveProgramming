#include <iostream>
#include <algorithm>
#define ONE_IS_GREATER 1
#define ZERO_IS_GREATER 0
#define EQUAL 2
#define DIV 16769023

int n;

long long dp[3][100001];

long long Find(int greater, int remain)
{
    if (remain <= 0)
        return 1;

    long long& result = dp[greater][remain];
    if (result != -1)
        return result;

    switch (greater)
    {
    case EQUAL:
        return result = (Find(ONE_IS_GREATER, remain - 1) + Find(ZERO_IS_GREATER, remain - 1)) % DIV;
        break;

    default:
        return result = Find(EQUAL, remain - 1) % DIV;
        break;
    }
}

int main()
{
    scanf("%d", &n);
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), -1);

    printf("%lld", Find(EQUAL, n));
}