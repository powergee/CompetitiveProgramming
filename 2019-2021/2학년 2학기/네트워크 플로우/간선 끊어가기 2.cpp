#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#define VERTEX_COUNT 501

int flow[VERTEX_COUNT][VERTEX_COUNT];
int capa[VERTEX_COUNT][VERTEX_COUNT];
int prev[VERTEX_COUNT];

int getSpare(int u, int v)
{
    return capa[u][v] - flow[u][v];
}

void addFlow(int u, int v, int add)
{
    flow[u][v] += add;
    flow[v][u] -= add;
}

bool findAugPath(int source, int sink)
{
    std::fill(prev, prev + VERTEX_COUNT, -1);
    std::queue<int> q;
    q.push(source);

    while (!q.empty() && prev[sink] == -1)
    {
        int now = q.front();
        q.pop();

        for (int next = 1; next < VERTEX_COUNT; ++next)
        {
            if (now != next && getSpare(now, next) > 0 && prev[next] == -1)
            {
                q.push(next);
                prev[next] = now;

                if (prev[sink] != -1)
                    break;
            }
        }
    }

    return prev[sink] != -1;
}

int edmondsKarp(int source, int sink)
{
    int result = 0;
    while (findAugPath(source, sink))
    {
        int add = INT32_MAX;

        for (int i = sink; i != source; i = prev[i])
            add = std::min(add, getSpare(prev[i], i));

        for (int i = sink; i != source; i = prev[i])
            addFlow(prev[i], i, add);

        result += add;
    }

    return result;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        capa[a][b] += c;
        capa[b][a] += c;
    }

    int s, t;
    scanf("%d %d", &s, &t);
    printf("%d", edmondsKarp(s, t));

    return 0;
}