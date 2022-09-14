#include <iostream>
#include <vector>

std::vector<int> graph[100001];
int parent[100001][21];
int depth[100001];
bool visited[100001];

void DFS(int start, int d)
{
    if (visited[start])
        return;

    depth[start] = d;
    visited[start] = true;

    for (int next : graph[start])
    {
        if (!visited[next])
        {
            DFS(next, d + 1);
            parent[next][0] = start;
        }
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N-1; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    DFS(1, 0);

    for (int exp = 1; exp < 21; ++exp)
        for (int child = 1; child <= N; ++child)
            parent[child][exp] = parent[ (parent[child][exp - 1]) ][exp - 1];

    int M;
    scanf("%d", &M);

    while (M--)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        if (depth[a] > depth[b])
            std::swap(a, b);
        
        for (int exp = 20; exp >= 0; --exp)
            if (depth[b] - depth[a] >= (1 << exp))
                b = parent[b][exp];

        if (a == b)
            printf("%d\n", a);
        else
        {
            for (int exp = 20; exp >= 0; --exp)
            {
                if (parent[a][exp] != parent[b][exp])
                {
                    a = parent[a][exp];
                    b = parent[b][exp];
                }
            }

            printf("%d\n", parent[a][0]);
        }
    }

    return 0;
}