#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;
int n, m, c;
Long income[1001];
// dp[s][t]: t시간에 s라는 정점에 있을 때 가능한 최대 수익
Long dp[1001][1001];
std::vector<std::pair<int, int>> edges;

int main()
{
    scanf("%d %d %d", &n, &m, &c);

    for (int i = 1; i <= n; ++i)
        scanf("%lld", income+i);
    
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        edges.emplace_back(u, v);
    }

    Long answer = 0;
    for (int i = 1; i <= 1000; ++i)
        dp[0][i] = -1;
    dp[0][1] = 0;

    for (int t = 1; t <= 1000; ++t)
    {
        for (int i = 1; i <= 1000; ++i)
            dp[t][i] = -1;
        for (std::pair<int, int>& edge : edges)
        {
            int u = edge.first;
            int v = edge.second;
            if (dp[t-1][u] != -1)
                dp[t][v] = std::max(dp[t][v], dp[t-1][u] + income[v]);
        }

        answer = std::max(answer, dp[t][1] - (Long)c*t*t);
    }

    printf("%lld", answer);

    return 0;
}