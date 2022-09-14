#include <iostream>
#include <algorithm>
#include <cmath>

int score[20][20];
bool inTeam[20];
int n;

int findAnswer(int count, int last)
{
    if (count == n/2)
    {
        int sum[2] = {0, 0};
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (inTeam[i] != inTeam[j] || i == j)
                    continue;
                
                if (inTeam[i])
                    sum[0] += score[i][j];
                else
                    sum[1] += score[i][j];
            }
        }

        return abs(sum[0] - sum[1]);
    }
    else
    {
        int result = 1e9;
        for (int i = last+1; i < n; ++i)
        {
            if (inTeam[i])
                continue;
            
            inTeam[i] = true;
            result = std::min(result, findAnswer(count+1, i));
            inTeam[i] = false;
        }

        return result;
    }
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &score[i][j]);
        
    printf("%d", findAnswer(0, -1));

    return 0;
}