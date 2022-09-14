#include <iostream>
#include <vector>
#include <queue>

std::vector<int> graph[501];
std::queue<std::pair<int, int>> q;
bool visited[501];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    q.push({1, 0});
    int count = 0;

    while (!q.empty())
    {
        auto now = q.front();
        q.pop();

        if (visited[now.first] || now.second > 2)
            continue;
        
        visited[now.first] = true;
        ++count;

        for (auto next : graph[now.first])
            if (!visited[next])
                q.push({next, now.second + 1});
    }

    printf("%d", count - 1);

    return 0;
}