#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

typedef long long Long;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<Long> height(n+1);
    std::for_each(height.begin()+1, height.end(), [](Long& h){ scanf("%lld", &h); });

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::priority_queue<std::pair<Long, int>> q;
    std::vector<Long> happiness(n+1, INT64_MIN/2);
    
    happiness[1] = 0;
    q.emplace(0LL, 1);

    while (!q.empty()) {
        auto curr = q.top().second;
        q.pop();

        for (int next : graph[curr]) {
            Long gain = (height[curr] < height[next] ? -2*(height[next]-height[curr]) : (height[curr]-height[next]));
            if (happiness[next] < happiness[curr] + gain) {
                happiness[next] = happiness[curr] + gain;
                q.emplace(happiness[next], next);
            }
        }
    }
    printf("%lld", *std::max_element(happiness.begin()+1, happiness.end()));

    return 0;
}