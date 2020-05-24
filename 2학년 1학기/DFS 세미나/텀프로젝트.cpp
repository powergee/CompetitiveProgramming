#include <iostream>
#include <vector>

std::vector<int> graph;
std::vector<bool> visited;
std::vector<bool> finished;
int cycleVerCount = 0;

void DFS(int start)
{
    if (finished[start])
        return;
    
    if (visited[start])
    {
        ++cycleVerCount;
        for (int next = graph[start]; next != start; next = graph[next])
            ++cycleVerCount;
        
        return;
    }

    visited[start] = true;
    if (!finished[start])
        DFS(graph[start]);

    finished[start] = true;
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
        finished.resize(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            int want;
            scanf("%d", &want);
            graph[i] = want;
        }

        for (int i = 1; i <= n; ++i)
            DFS(i);
        printf("%d\n", n - cycleVerCount);
        
        graph.clear();
        visited.clear();
        finished.clear();
        cycleVerCount = 0;
    }

    return 0;
}