#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

const int SPARSE_MAX = 20;

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d:\n", t);
        int n, q, cap;
        scanf("%d %d %d", &n, &q, &cap);

        std::vector<std::vector<int>> tree(n+1);
        for (int i = 0; i < n-1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            tree[u].emplace_back(v);
            tree[v].emplace_back(u);
        }

        std::vector<int> depth(n+1, 0);
        std::vector<int> count(n+1, 1);
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
            for (int next : tree[start]) {
                if (parent[next][0] == 0) {
                    initLCA(next, currDepth+1, start);
                    count[start] += count[next];
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

        while (q--) {
            int s, u;
            scanf("%d %d", &s, &u);
            int lca = findLCA(cap, u);

            if (s == 0) {
                cap = u;
            } else if (cap == u) {
                printf("%d\n", n);
            } else if (lca == u) {
                int child = cap;
                for (int i = SPARSE_MAX-1; i >= 0; --i) {
                    if (depth[u] < depth[parent[child][i]]) {
                        child = parent[child][i];
                    }
                }
                printf("%d\n", n-count[child]);
            } else {
                printf("%d\n", count[u]);
            }
        }
    }

    return 0;
}