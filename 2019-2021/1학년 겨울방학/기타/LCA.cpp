#include <iostream>
#include <vector>

std::vector<int> graph[50001];
int parent[50001];
int depth[50001];
bool visited[50001];

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
            parent[next] = start;
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

    int M;
    scanf("%d", &M);

    while (M--)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        int aDep = depth[a];
        int bDep = depth[b];

        if (aDep > bDep)
        {
            std::swap(aDep, bDep);
            std::swap(a, b);
        }

        while (aDep < bDep)
        {
            --bDep;
            b = parent[b];
        }

        while (a != b)
        {
            a = parent[a];
            b = parent[b];
        }

        printf("%d\n", a);
    }

    return 0;
}