#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> tree(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    const int SPARSE_MAX = 20;

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
        for (int next : tree[start]) {
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

    auto findCircumcenter = [&](int a, int b, int c) -> int {
        int abLCA = findLCA(a, b);
        int bcLCA = findLCA(b, c);
        int acLCA = findLCA(a, c);
        int globalLCA = findLCA(a, bcLCA);
        int abDist = depth[a] + depth[b] - 2*depth[abLCA];
        int bcDist = depth[b] + depth[c] - 2*depth[bcLCA];
        int acDist = depth[a] + depth[c] - 2*depth[acLCA];

        int radius;
        if (abDist == bcDist && abDist >= acDist && abDist % 2 == 0) {
            radius = abDist / 2;
        } else if (bcDist == acDist && bcDist >= abDist && bcDist % 2 == 0) {
            radius = bcDist / 2;
        } else if (acDist == abDist && acDist >= bcDist && acDist % 2 == 0) {
            radius = acDist / 2;
        } else {
            return -1;
        }

        int aDepth = depth[a] - depth[globalLCA];
        int bDepth = depth[b] - depth[globalLCA];
        int cDepth = depth[c] - depth[globalLCA];
        if (aDepth >= bDepth && aDepth >= cDepth) {
            return findKthParent(a, radius);
        } else if (bDepth >= aDepth && bDepth >= cDepth) {
            return findKthParent(b, radius);
        } else {
            return findKthParent(c, radius);
        }
    };

    int q;
    scanf("%d", &q);

    while (q--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        printf("%d\n", findCircumcenter(a, b, c));
    }

    return 0;
}