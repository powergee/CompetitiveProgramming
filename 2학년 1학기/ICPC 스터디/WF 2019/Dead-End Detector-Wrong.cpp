#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int n, m;
std::vector<int> graph[500001];
std::vector<std::pair<int, int>> answer;

bool hasCycle(std::vector<int>& component)
{
    static bool visited[500001];
    std::queue<std::pair<int, int>> q;
    q.push({component[0], 0});

    while (!q.empty())
    {
        auto now = q.front();
        q.pop();
        if (visited[now.first])
            return true;
        visited[now.first] = true;

        for (int next : graph[now.first])
        {
            if (next == now.second)
                continue;
            if (visited[next])
                return true;
            
            q.push({next, now.first});
        }
    }

    return false;
}

void putDeadEndSigns(std::vector<int>& component)
{
    if (hasCycle(component))
    {
        std::queue<std::pair<int, int>> leafQ;
        for (int v : component)
            if ((int)graph[v].size() == 1)
                leafQ.push({v, 0});
        
        static bool passed[500001];
        static std::vector<int> signs[500001];
        while (!leafQ.empty())
        {
            std::pair<int, int> now = leafQ.front();
            leafQ.pop();
            
            int passedCount = 0, notPassed;
            for (int connected : graph[now.first])
            {
                if (passed[connected])
                    ++passedCount;
                else notPassed = connected;
            }
            
            if ((int)graph[now.first].size() - passedCount == 1)
            {
                signs[now.first].resize(0);
                leafQ.push({notPassed, now.first});
                passed[now.first] = true;
            }
            else if ((int)graph[now.first].size() - passedCount > 1)
            {
                signs[now.first].push_back(now.second);
            }
        }

        for (int u : component)
            for (int v : signs[u])
                answer.push_back({u, v});
    }
    else
    {
        for (int v : component)
            if ((int)graph[v].size() == 1)
                answer.push_back({v, graph[v][0]});
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    static bool visited[500001];
    for (int i = 1; i <= n; ++i)
    {
        if (visited[i])
            continue;

        std::vector<int> component;
        std::queue<int> q;
        q.push(i);

        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            if (visited[now])
                continue;
            
            visited[now] = true;
            component.push_back(now);

            for (int next : graph[now])
                if (!visited[next])
                    q.push(next);
        }

        putDeadEndSigns(component);
    }

    std::sort(answer.begin(), answer.end());
    std::cout << answer.size() << "\n";
    for (auto p : answer)
        std::cout << p.first << " " << p.second << "\n";

    return 0;
}