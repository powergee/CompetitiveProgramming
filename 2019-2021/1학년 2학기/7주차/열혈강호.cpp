#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> graph[1001];

bool visited[1001];
int matching[1001];

int DFS(int start)
{
    if (visited[start])
        return 0;
    
    visited[start] = true;

    for (int next : graph[start])
    {
        if (matching[next] == 0 || DFS(matching[next]))
        {
            matching[next] = start;
            return 1;
        }
    }

    return 0;
}

int Bipartite(int N)
{
    int result = 0;
    for (int i = 1; i <= N; i++)
    {
        std::fill(visited, visited + N, false);
        if (DFS(i))
            ++result;
    }

    return result;
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; ++i)
    {
        int count;
        scanf("%d", &count);

        for (int j = 0; j < count; ++j)
        {
            int canDo;
            scanf("%d", &canDo);

            graph[i].push_back(canDo);
        }
    }

    printf("%d", Bipartite(N));

    return 0;
}