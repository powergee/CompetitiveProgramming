#include <iostream>
#include <algorithm>

int arr[100000];
int n;
int dp[100000][2];

int canWin(int start, int strictlyOne)
{
    int& result = dp[start][strictlyOne];
    if (result != -1)
        return result;

    if (start == n-1)
        return result = 1;
    
    if (arr[start] == 1 || strictlyOne)
        return result = (canWin(start + 1, 0) ? 0 : 1);
    else
        return result = (canWin(start + 1, 0) || canWin(start, 1) ? 1 : 0);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);
        
        if (canWin(0, 0))
            printf("First\n");
        else printf("Second\n");
    }

    return 0;
}