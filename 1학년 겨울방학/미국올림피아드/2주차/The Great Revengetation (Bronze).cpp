#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

std::vector<std::vector<int>> graph;
char result[102];

char FillResult(int pos)
{
    for (char ret = '1'; ret <= '4'; ++ret)
    {
        bool able = true;

        for (int conn : graph[pos])
        {
            if (result[conn] == ret)
            {
                able = false;
                break;
            }
        }

        if (able)
            return ret;
    }

    return '-';
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    graph.resize(N + 1);
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= N; ++i)
        result[i] = FillResult(i);
    printf("%s", result + 1);
}