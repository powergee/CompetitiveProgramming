#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define INF 100000000
using namespace std;

int edges[101][101];
int dist[101][101];
int path[101][101];
int N, M;

void GetPath(int start, int end, queue<int>& result)
{
    if (path[start][end] == 0)
        return;

    result.push(start);
    while (start != end)
    {
        start = path[start][end];
        result.push(start);
    }
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        int start, end, cost;
        scanf("%d %d %d", &start, &end, &cost);

        if (edges[start][end] == 0)
            edges[start][end] = cost;
        else
            edges[start][end] = min(edges[start][end], cost);
    }

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            if (i == j)
                dist[i][j] = 0;
            else if (edges[i][j]) 
            {
                dist[i][j] = edges[i][j];
                path[i][j] = j;
            }
            else dist[i][j] = INF;
        }

    for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
            printf("%d ", dist[i][j] >= INF ? 0 : dist[i][j]);

        printf("\n");
    }

    queue<int> pathQueue;
    int qSize;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            GetPath(i, j, pathQueue);
            printf("%d ", qSize = pathQueue.size());

            if (qSize)
            {
                while (!pathQueue.empty())
                {
                    printf("%d ", pathQueue.front());
                    pathQueue.pop();
                }
            }
            printf("\n");
        }
    }
    
    return 0;
}