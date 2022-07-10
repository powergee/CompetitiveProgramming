#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

const int SPARSE_MAX = 20;

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

    int q;
    scanf("%d", &q);

    while (q--) {
        int m;
        scanf("%d", &m);
        std::vector<int> query(m);
        for (int i = 0; i < m; ++i) {
            scanf("%d", &query[i]);
        }

        auto isPath = [&]() -> bool {
            auto bottom = std::min_element(query.begin(), query.end(), [&](int v1, int v2) {
                return depth[v1] > depth[v2];
            });
            int bottomIndex = bottom - query.begin();
            
            std::vector<int> parentTeam, jointTeam;
            int joint = -1;
            parentTeam.push_back(*bottom);

            for (int i = 0; i < m; ++i) {
                if (i == bottomIndex) {
                    continue;
                }

                int lca = findLCA(*bottom, query[i]);
                if (lca == query[i]) {
                    parentTeam.push_back(query[i]);
                } else if (joint == -1) {
                    joint = lca;
                    jointTeam.push_back(query[i]);
                } else if (joint != lca) {
                    return false;
                } else {
                    jointTeam.push_back(query[i]);
                }
            }

            if (jointTeam.empty()) {
                return true;
            }

            // joint must be a parent of all of parent team
            for (int p : parentTeam) {
                if (findLCA(p, joint) != joint) {
                    return false;
                }
            }

            auto jointBottom = std::min_element(jointTeam.begin(), jointTeam.end(), [&](int v1, int v2) {
                return depth[v1] > depth[v2];
            });
            int jointBottomIndex = jointBottom - jointTeam.begin();
            for (int i = 0; i < jointTeam.size(); ++i) {
                if (i == jointBottomIndex) {
                    continue;
                }
                int lca = findLCA(*jointBottom, jointTeam[i]);
                if (lca != jointTeam[i]) {
                    return false;
                }
            }
            return true;
        };

        printf(isPath() ? "YES\n" : "NO\n");
    }

    return 0;
}