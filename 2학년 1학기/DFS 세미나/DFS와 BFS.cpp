#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

std::vector<int> graph[1001];
bool visited[1001];

void DFS(int start)
{
    if (visited[start])
        return;

    visited[start] = true;
    printf("%d ", start);

    for (int next : graph[start])
        DFS(next);
}

void BFS(int start)
{
    std::queue<int> q;
    q.push(start);

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        if (visited[now])
            continue;
        visited[now] = true;
        printf("%d ", now);

        for (int next : graph[now])
            if (!visited[next])
                q.push(next);
    }
}

int main()
{
    int n, m, v;
    scanf("%d %d %d", &n, &m, &v);

    for (int i = 0; i < m; ++i)
    {
        int s, e;
        scanf("%d %d", &s, &e);
        graph[s].push_back(e);
        graph[e].push_back(s);
    }

    for (int i = 1; i <= n; ++i)
        std::sort(graph[i].begin(), graph[i].end());
    
    DFS(v);
    printf("\n");
    std::fill(visited, visited + n + 1, false);
    BFS(v);

    return 0;
}