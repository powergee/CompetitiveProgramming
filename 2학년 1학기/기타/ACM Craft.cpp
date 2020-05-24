#include <iostream>
#include <algorithm>
#include <vector>

int dp[1001];
int delay[1001];
std::vector<std::vector<int>> graph;

int GetTime(int num)
{
    if (graph[num].empty())
        return delay[num];
    
    int& result = dp[num];
    if (result != -1)
        return result;

    int maxParent = -1;
    for (int parent : graph[num])
        maxParent = std::max(maxParent, GetTime(parent));

    result = maxParent + delay[num];
    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);

        std::fill(dp, dp + n + 1, -1);
        graph.clear();
        graph.resize(n + 1);

        for (int i = 0; i < n; ++i)
            scanf("%d", delay + i + 1);
        
        for (int i = 0; i < k; ++i)
        {
            int first, next;
            scanf("%d%d", &first, &next);
            graph[next].push_back(first);
        }

        int goal;
        scanf("%d", &goal);
        printf("%d\n", GetTime(goal));
    }

    return 0;
}