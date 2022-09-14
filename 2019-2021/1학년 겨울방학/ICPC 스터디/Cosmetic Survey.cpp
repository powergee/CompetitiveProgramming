#include <iostream>
#include <algorithm>
#include <functional>
#include <limits>
#define INF (INT32_MAX/2)

int cosNum, evaNum;
int d[500][500];
std::pair<int, int> survey[500];

int dist[500][500];

int main()
{
    scanf("%d %d", &cosNum, &evaNum);

    for (int i = 0; i < evaNum; ++i)
    {
        for (int j = 0; j < cosNum; ++j)
        {
            scanf("%d", &survey[j].first);

            if (survey[j].first == 0)
                survey[j].first = INT32_MAX;

            survey[j].second = j;
        }

        std::sort(survey, survey + cosNum);

        for (int better = 0; better < cosNum; ++better)
        {
            for (int worse = better + 1; worse < cosNum; ++worse)
            {
                if (survey[better].first != survey[worse].first)
                    ++d[survey[better].second][survey[worse].second];
            }
        }
    }

    for (int i = 0; i < cosNum; ++i)
    {
        for (int j = 0; j < cosNum; ++j)
        {
            if (i == j)
                dist[i][j] = INF;
            else dist[i][j] = 0;
        }
    }

    for (int a = 0; a < cosNum; ++a)
    {
        for (int b = 0; b < cosNum; ++b)
        {
            if (a == b)
                continue;
            
            if (d[a][b] > d[b][a])
            {
                dist[a][b] = d[a][b];
            }
        }        
    }

    for (int med = 0; med < cosNum; ++med)
    {
        for (int start = 0; start < cosNum; ++start)
        {
            for (int end = 0; end < cosNum; ++end)
            {
                dist[start][end] = std::max(dist[start][end], std::min(dist[start][med], dist[med][end]));
            }
        }
    }
    
    for (int x = 0; x < cosNum; ++x)
    {
        bool isAnswer = true;

        for (int y = 0; y < cosNum; ++y)
        {
            if (dist[x][y] < dist[y][x])
            {
                isAnswer = false;
                break;
            }
        }

        if (isAnswer)
            printf("%d ", x + 1);
    }

    return 0;
}