#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#define VERTEX_COUNT 401

int flow[VERTEX_COUNT][VERTEX_COUNT];
int capa[VERTEX_COUNT][VERTEX_COUNT];
int prev[VERTEX_COUNT];

int GetSpare(int u, int v)
{
    return capa[u][v] - flow[u][v];
}

void AddFlow(int u, int v, int add)
{
    flow[u][v] += add;
    flow[v][u] -= add;
}

bool FindAugPath(int source, int sink)
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
            if (now != next && GetSpare(now, next) > 0 && prev[next] == -1)
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

int EdmondsKarp(int source, int sink)
{
    int result = 0;
    while (FindAugPath(source, sink))
    {
        int add = INT32_MAX;

        for (int i = sink; i != source; i = prev[i])
            add = std::min(add, GetSpare(prev[i], i));

        for (int i = sink; i != source; i = prev[i])
            AddFlow(prev[i], i, add);

        result += add;
    }

    return result;
}

int main()
{
    int n, p;
    scanf("%d %d", &n, &p);

    while (p--)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        capa[u][v] += 1;
    }

    printf("%d", EdmondsKarp(1, 2));

    return 0;
}