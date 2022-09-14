#include <iostream>
#include <algorithm>
#define INF ((Long)1e13)

typedef long long Long;

Long dist[500][500];
bool visited[500];

bool FloydWarshall(int n)
{
    bool changed = false;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    changed = true;
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return changed;
}

void DFS(int start, int n)
{
    visited[start] = true;

    for (int i = 0; i < n; ++i)
        if (start != i && dist[start][i] != INF && !visited[i])
            DFS(i, n);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    std::fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(Long), INF);

    for (int i = 0; i < m; ++i)
    {
        int s, e;
        Long d;
        scanf("%d %d %lld", &s, &e, &d);
        dist[s - 1][e - 1] = std::min(d, dist[s - 1][e - 1]);
    }

    DFS(0, n);

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            for (int j = 0; j < n; ++j)
                dist[j][i] = INF;
            for (int j = 0; j < n; ++j)
                dist[i][j] = INF;
        }
    }

    FloydWarshall(n);

    if (FloydWarshall(n))
    {
        printf("-1");
    }
    else
    {
        for (int i = 1; i < n; ++i)
            printf("%lld\n", (dist[0][i] == INF ? -1 : dist[0][i]));
    }

    return 0;
}