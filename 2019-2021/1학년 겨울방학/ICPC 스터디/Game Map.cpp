#include <iostream>
#include <vector>
#include <algorithm>

int n, m;
std::vector<int> graph[100000];
int conn[100000];
int memo[100000];

int DFS(int start)
{
    int& result = memo[start];
    if (result != -1)
        return result;

    result = 1;
    for (int next : graph[start])
    {
        if (conn[start] < conn[next])
            result = std::max(DFS(next) + 1, result);
    }
    
    return result;
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
        ++conn[u];
        ++conn[v];
    }

    int result = 0;
    std::fill(memo, memo + n, -1);
    for (int v = 0; v < n; ++v)
        result = std::max(result, DFS(v));

    printf("%d", result);

    return 0;
}