#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<bool> visited;
std::vector<int> visitCount;

void DFS(int start)
{
    ++visitCount[start];
    visited[start] = true;

    for (int next : graph[start])
    {
        if (!visited[next])
            DFS(next);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    graph.resize(n + 1);
    visited.resize(n + 1);
    visitCount.resize(n + 1);

    std::fill(visitCount.begin(), visitCount.end(), 0);

    for (int i = 1; i < n; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        graph[a].push_back(b);
    }

    for (int start = 1; start <= n; ++start)
    {
        std::fill(visited.begin(), visited.end(), false);
        DFS(start);
    }

    for (int i = 1; i <= n; ++i)
    {
        if (visitCount[i] == n)
        {
            printf("%d", i);
            return 0;
        }
    }

    printf("-1");
    return 0;
}