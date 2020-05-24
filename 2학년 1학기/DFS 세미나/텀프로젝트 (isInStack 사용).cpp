#include <iostream>
#include <vector>

std::vector<int> graph;
std::vector<bool> visited;
std::vector<bool> isInStack;
int cycleVerCount = 0;

void DFS(int start)
{
    if (isInStack[start])
    {
        ++cycleVerCount;
        for (int next = graph[start]; next != start; next = graph[next])
            ++cycleVerCount;
        
        return;
    }
    // 앞 슬라이드에서 이어짐...

    if (visited[start])
        return;

    visited[start] = true;
    isInStack[start] = true;

    if (graph[start] != 0)
        DFS(graph[start]);
    
    isInStack[start] = false;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        // 문제 상황을 적절히 입력 받음...
        int n;
        scanf("%d", &n);
        graph.resize(n + 1);
        visited.resize(n + 1);
        isInStack.resize(n + 1);

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
        isInStack.clear();
        cycleVerCount = 0;
    }

    return 0;
}