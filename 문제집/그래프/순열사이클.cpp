#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> graph[1001];
bool visited[1001];

void DFS(int start, std::vector<int>* graph, bool* visited)
{
    if (visited[start])
        return;

    visited[start] = true;

    for (auto i = graph[start].begin(); i != graph[start].end(); ++i)
    {
        if (!visited[*i])
        {
            DFS(*i, graph, visited);
        }
    }
}

int main()
{
    int tc;
    scanf("%d", &tc);

    while (tc--)
    {
        for (int i = 0; i < 1001; ++i)
            graph[i].clear();

        std::fill(visited, visited + 1001, false);

        int N;
        scanf("%d", &N);

        for (int i = 1; i <= N; ++i)
        {
            int element;
            scanf("%d", &element);

            graph[i].push_back(element);
        }

        int count = 0;
        for (int i = 1; i <= N; ++i)
        {
            if (!visited[i])
            {
                DFS(i, graph, visited);
                ++count;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}