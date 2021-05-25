#include <iostream>
#include <algorithm>
#include <vector>

using Long = long long;

using Vertex = std::pair<Long, Long>;

std::vector<Vertex> vertices;
std::vector<int> graph[100000];
bool visiting[100000];
Long dp[100000][2];

Long getMax(int start, int choseLeft) {
    Long& result = dp[start][choseLeft];
    if (result != -1) {
        return result;
    }

    Long chosen = choseLeft ? vertices[start].first : vertices[start].second;
    result = 0;
    visiting[start] = true;

    for (int next : graph[start]) {
        if (visiting[next]) {
            continue;
        }

        Long d1 = std::abs(chosen - vertices[next].first) + getMax(next, 1);
        Long d2 = std::abs(chosen - vertices[next].second) + getMax(next, 0);
        result += std::max(d1, d2);
    }

    visiting[start] = false;
    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            Long s, e;
            scanf("%lld %lld", &s, &e);
            vertices.emplace_back(s, e);
            dp[i][0] = dp[i][1] = -1;
        }
        
        for (int i = 0; i < n-1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        printf("%lld\n", std::max(getMax(0, 0), getMax(0, 1)));

        vertices.clear();
        for (int i = 0; i < n; ++i) {
            graph[i].clear();
        }
    }

    return 0;
}