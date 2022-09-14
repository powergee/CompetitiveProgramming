#include <iostream>
#include <vector>

std::vector<int> graph;
std::vector<bool> visited;

void DFS(int start)
{
    if (visited[start])
        return;

    visited[start] = true;
    DFS(graph[start]);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        graph.resize(n + 1);
        visited.resize(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            int to;
            scanf("%d", &to);
            graph[i] = to;
        }
        
        int cycleCount = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (!visited[i])
            {
                DFS(i);
                ++cycleCount;
            }
        }
        printf("%d\n", cycleCount);
        
        graph.clear();
        visited.clear();
    }

    return 0;
}