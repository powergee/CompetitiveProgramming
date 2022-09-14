#include <iostream>
#include <algorithm>
#include <vector>

using Long = long long;

struct Edge {
    int dst, cost;
};

int n;
int countDP[10000];
Long costDP[10000];
std::vector<Edge> graph[10000];

void initDP(int start, int parent) {
    countDP[start] = 1;
    costDP[start] = 0;

    for (auto& e : graph[start]) {
        if (e.dst != parent) {
            initDP(e.dst, start);
            countDP[start] += countDP[e.dst];
            costDP[start] += e.cost * countDP[e.dst] + costDP[e.dst];
        }
    }
}

Long getMinCost(int start, int parent, Long currCost) {
    Long result = currCost;

    for (auto& e : graph[start]) {
        if (e.dst != parent) {
            Long nextCost = getMinCost(e.dst, start, currCost - (countDP[e.dst]*e.cost) + ((n-countDP[e.dst])*e.cost));
            result = std::min(result, nextCost);
        }
    }

    return result;
}

int main() {
    while (scanf("%d", &n), n > 0) {
        std::fill(countDP, countDP+n, -1);
        std::fill(costDP, costDP+n, -1);
        for (int i = 0; i < n; ++i) {
            graph[i].clear();
        }

        for (int i = 0; i < n-1; ++i) {
            int a, b, w;
            scanf("%d %d %d", &a, &b, &w);
            graph[a].push_back({b, w});
            graph[b].push_back({a, w});
        }

        initDP(0, -1);
        printf("%lld\n", getMinCost(0, -1, costDP[0]));
    }

    return 0;
}