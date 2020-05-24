#include <iostream>
#include <algorithm>

int arr[2000];
int dp[2000][2000];

int Query(int start, int end)
{
    if (start >= end)
        return 1;

    int& ret = dp[start][end];
    if (ret != -1)
        return ret;

    bool palin;
    if (arr[start - 1] == arr[end - 1])
        palin = (Query(start + 1, end - 1) == 1);
    else
        palin = false;

    return ret = (palin ? 1 : 0);
}

int main()
{
    int arrSize;
    scanf("%d", &arrSize);

    for (int i = 0; i < arrSize; ++i)
    {
        scanf("%d", arr + i);
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);

    int qCount;
    scanf("%d", &qCount);

    for (int i = 0; i < qCount; ++i)
    {
        int s, e;
        scanf("%d %d", &s, &e);

        printf("%d\n", Query(s, e));
    }

    return 0;
}