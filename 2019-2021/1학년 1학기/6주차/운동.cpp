#include <iostream>
#include <vector>
#include <queue>
#define INF 100000000
using namespace std;

int edges[401][401];
int dist[401][401];
int path[401][401];
int N, M;

int GetCycleLength(int cycleStart)
{
    if (path[cycleStart][cycleStart] == 0)
        return INF;

    return dist[cycleStart][cycleStart];
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        edges[a][b] = c;
    }

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            if (edges[i][j])
            {
                dist[i][j] = edges[i][j];
                path[i][j] = j;
            }
            else dist[i][j] = INF;
        }
    }

    for (int k = 1; k <= N; ++k)
    {
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    int minResult = GetCycleLength(1);
    for (int i = 2; i <= N; ++i)
    {
        minResult = min(GetCycleLength(i), minResult);
    }

    printf("%d", minResult == INF ? -1 : minResult);

    return 0;
}