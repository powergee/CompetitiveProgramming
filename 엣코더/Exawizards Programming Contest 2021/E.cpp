#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

struct Edge {
    int u, v;
    int appeared = 0;

    int next(int curr) {
        return curr == u ? v : u;
    }
};

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    std::vector<int> points(m);
    std::vector<Edge*> edges;
    std::vector<std::vector<Edge*>> tree(n+1);

    for (int i = 0; i < m; ++i) {
        scanf("%d", &points[i]);
    }
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);

        Edge* e = new Edge;
        e->u = u;
        e->v = v;
        edges.push_back(e);
        tree[u].push_back(e);
        tree[v].push_back(e);
    }

    auto findPath = [&](int start, int end) -> std::vector<Edge*> {
        std::vector<Edge*> result;
        std::vector<bool> visited(n+1, false);

        std::function<bool(int)> DFS;
        DFS = [&](int curr) -> bool {
            if (curr == end) {
                return true;
            }

            visited[curr] = true;
            for (Edge* e : tree[curr]) {
                int next = e->next(curr);
                if (!visited[next]) {
                    result.push_back(e);
                    if (DFS(next)) {
                        return true;
                    }
                    result.pop_back();
                }
            }
            return false;
        };

        DFS(start);
        return result;
    };

    for (int i = 0; i < m-1; ++i) {
        auto path = findPath(points[i], points[i+1]);
        for (auto e : path) {
            e->appeared++;
        }
    }

    int total = 0;
    for (auto e : edges) {
        total += e->appeared;
    }

    if ((total + k) % 2 == 0) {
        int goal = std::abs((total+k) / 2);
        std::vector<std::vector<Long>> dp(n-1, std::vector<Long>(goal+1, -1LL));

        std::function<Long(int, int)> countCases;
        countCases = [&](int eIdx, int goal) -> Long {
            if (goal < 0) {
                return 0;
            }
            if (eIdx == n-1) {
                return (goal > 0 ? 0 : 1);
            }
            if (dp[eIdx][goal] != -1LL) {
                return dp[eIdx][goal];
            }

            dp[eIdx][goal] = countCases(eIdx+1, goal) + countCases(eIdx+1, goal-edges[eIdx]->appeared);
            dp[eIdx][goal] %= 998244353LL;
            return dp[eIdx][goal];
        };

        printf("%lld", countCases(0, goal));
    } else {
        printf("0");
    }

    return 0;
}