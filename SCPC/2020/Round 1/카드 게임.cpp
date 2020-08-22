#include <iostream>
#include <algorithm>

int cards[2][3000];
int n, k;
int dp[3001][3001];

bool ableToWin(int spare1, int spare2)
{
    int& result = dp[spare1][spare2];
    if (result != -1)
        return result;

    if (spare1 == 0 && spare2 == 0)
        return result = true;
    else if ((spare1 == 0 && spare2 == 1) || (spare1 == 1 && spare2 == 0))
        return result = false;

    
    result = 0;
    int sum = 0;
    for (int i = spare1 - 1; i >= 0; --i)
    {
        if (sum + cards[0][i] > k)
            break;
        
        sum += cards[0][i];
        if (!ableToWin(i, spare2))
            return result = true;
    }
    
    sum = 0;
    for (int i = spare2 - 1; i >= 0; --i)
    {
        if (sum + cards[1][i] > k)
            break;
        
        sum += cards[1][i];
        if (!ableToWin(spare1, i))
            return result = true;
    }

    result = false;

    sum = 0;
    for (int i = spare1+1; i <= n; ++i)
    {
        sum += cards[0][i-1];
        if (sum > k)
            break;
        
        dp[i][spare2] = true;
    }

    sum = 0;
    for (int i = spare2+1; i <= n; ++i)
    {
        sum += cards[1][i-1];
        if (sum > k)
            break;
        
        dp[spare1][i] = true;
    }

    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d\n", t);

        scanf("%d %d", &n, &k);
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &cards[i][j]);
        
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                dp[i][j] = -1;
        
        int win = 0, lose = 0;
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                if (ableToWin(i, j))
                    ++win;
                else
                    ++lose;
            }
        }

        printf("%d %d\n", win, lose);
    }

    return 0;
}