#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

std::vector<int> graph[101001];
bool visited[101001];
bool pushed[101001];

int main()
{
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            int st;
            scanf("%d", &st);
            graph[st].push_back(100001 + i);
            graph[100001 + i].push_back(st);
        }
    }

    std::queue<std::pair<int, int>> q;
    q.push({1, 1});
    pushed[1] = true;
    int dist = -1;

    while (!q.empty() && dist == -1)
    {
        std::pair<int, int> now = q.front();
        q.pop();

        if (visited[now.first])
            continue;
        visited[now.first] = true;

        if (now.first == n)
            dist = now.second;
        else
        {
            for (int next : graph[now.first])
            {
                if (!visited[next] && !pushed[next])
                {
                    q.push({next, now.second + (next > 100000 ? 0 : 1)});
                    pushed[next] = true;
                }
            }
        }
    }

    printf("%d", dist);

    return 0;
}