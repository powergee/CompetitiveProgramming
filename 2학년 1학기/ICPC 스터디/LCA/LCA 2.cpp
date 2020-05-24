#include <iostream>
#include <algorithm>
#include <vector>

int n, m;
std::vector<int> graph[100001];
int parent[100001][18];
int visited[100001];
int depth[100001];

void DFS(int start, int d)
{
    visited[start] = true;
    depth[start] = d;

    for (int next : graph[start])
    {
        if (!visited[next])
        {
            parent[next][0] = start;
            DFS(next, d + 1);
        }
    }
}

void InitLCA()
{
    DFS(1, 0);

    for (int exp = 1; exp < 18; ++exp)
        for (int node = 1; node <= n; ++node)
            parent[node][exp] = parent[parent[node][exp - 1]][exp - 1];
}

int LCA(int x, int y)
{
    if (depth[x] < depth[y])
        std::swap(x, y);
    
    // 이 시점에서 x의 깊이가 y보다 깊음.
    for (int exp = 17; exp >= 0; --exp)
        if (depth[x] - depth[y] >= (1 << exp))
            x = parent[x][exp];

    if (x == y)
        return x;

    for (int exp = 17; exp >= 0; --exp)
    {
        if (parent[x][exp] != parent[y][exp])
        {
            x = parent[x][exp];
            y = parent[y][exp];
        }
    }

    return parent[x][0];
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n - 1; ++i)
    {
        int s, e;
        scanf("%d %d", &s, &e);
        graph[s].push_back(e);
        graph[e].push_back(s);
    }

    InitLCA();
    scanf("%d", &m);

    for (int i = 0; i < m; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", LCA(x, y));
    }

    return 0;
}