#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<bool> visited;
std::vector<bool> isInStack;

bool DFS(int start)
{
    if (isInStack[start])
        return true;
    
    if (visited[start])
        return false;
    
    visited[start] = true;
    isInStack[start] = true;

    for (int next : graph[start])
        if (DFS(next))
            return true;

    isInStack[start] = false;
    return false;
}

int main()
{
    int n;
    scanf("%d", &n);
    graph.resize(n + 1);
    visited.resize(n + 1);
    isInStack.resize(n + 1);

    while (true)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u == -1 || v == -1)
            break;

        graph[u].push_back(v);
    }

    bool hasCycle = false;
    for (int i = 1; i <= n && !hasCycle; ++i)
        hasCycle = DFS(i);
    
    if (hasCycle)
        printf("이 그래프에는 사이클이 있습니다! (O)");
    else 
        printf("이 그래프에는 사이클이 없습니다! (X)");

    return 0;
}