#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<std::pair<int, Long>>> tree(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        Long c;
        scanf("%d %d %lld", &u, &v, &c);
        tree[u].emplace_back(v, c);
        tree[v].emplace_back(u, c);
    }

    const int SPARSE_MAX = 20;

    std::vector<Long> absCost(n+1, -1);
    std::function<void(int, Long)> initCost = [&](int start, Long prevCost) {
        absCost[start] = prevCost;
        for (auto [next, currCost] : tree[start]) {
            if (absCost[next] == -1) {
                initCost(next, prevCost+currCost);
            }
        }
    };
    initCost(1, 0);

    std::vector<int> depth(n+1, 0);
    std::vector<std::vector<int>> parent(n+1, std::vector<int>(SPARSE_MAX, 0));

    for (int i = 0; i < SPARSE_MAX; ++i) {
        parent[1][i] = 1;
    }
    std::function<void(int, int, int)> initLCA = [&](int start, int currDepth, int upper) {
        depth[start] = currDepth;
        parent[start][0] = upper;
        for (int i = 1; i < SPARSE_MAX; ++i) {
            parent[start][i] = parent[parent[start][i-1]][i-1];
        }
        for (auto [next, _] : tree[start]) {
            if (parent[next][0] == 0) {
                initLCA(next, currDepth+1, start);
            }
        }
    };
    initLCA(1, 0, 1);

    auto findKthParent = [&](int u, int k) -> int {
        for (int i = 0; i < SPARSE_MAX; ++i) {
            if (k & (1<<i)) {
                u = parent[u][i];
            }
        }
        return u;
    };

    auto findLCA = [&](int u, int v) -> int {
        int d1 = depth[u], d2 = depth[v];
        int lower = d1 < d2 ? v : u;
        int upper = d1 < d2 ? u : v;
        lower = findKthParent(lower, depth[lower] - depth[upper]);

        if (lower != upper) {
            for (int i = SPARSE_MAX-1; i >= 0; --i) {
                if (parent[lower][i] != parent[upper][i]) {
                    lower = parent[lower][i];
                    upper = parent[upper][i];
                }
            }
            lower = parent[lower][0];
            upper = parent[upper][0];
        }

        return lower;
    };

    int q;
    scanf("%d", &q);

    while (q--) {
        int comm;
        scanf("%d", &comm);
        if (comm == 1) {
            int u, v;
            scanf("%d %d", &u, &v);
            int lca = findLCA(u, v);
            printf("%lld\n", absCost[u] + absCost[v] - 2*absCost[lca]);
        } else {
            int u, v, k;
            scanf("%d %d %d", &u, &v, &k);
            int lca = findLCA(u, v);
            int uDist = depth[u] - depth[lca];
            int vDist = depth[v] - depth[lca];
            if (k <= uDist+1) {
                printf("%d\n", findKthParent(u, k-1));
            } else {
                printf("%d\n", findKthParent(v, uDist+vDist+1-k));
            }
        }
    }

    return 0;
}