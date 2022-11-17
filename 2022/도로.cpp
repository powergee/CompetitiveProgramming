#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <tuple>
#include <algorithm>

typedef long long Long;

class DisjointSet {
private:
    std::vector<int> parent;
public:
    DisjointSet(int count) {
        parent.resize(count);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int findParent(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = findParent(parent[x]);
    }

    void unionNodes(int x, int y) {
        int xPar = findParent(x);
        int yPar = findParent(y);
        parent[xPar] = yPar;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        int n, m, p, q;
        std::cin >> n >> m >> p >> q;
        if (p > q) {
            std::swap(p, q);
        }
        Long queryW = -1;
        std::vector<std::tuple<int, int, Long>> edges(m);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            std::cin >> u >> v >> w;
            edges[i] = { u, v, w };
            if (u > v) {
                std::swap(u, v);
            }
            if (u == p && v == q) {
                assert(queryW == -1);
                queryW = w;
            }
        }
        assert(queryW != -1);
        std::sort(edges.begin(), edges.end(), [](auto t1, auto t2) {
            return std::get<2>(t1) < std::get<2>(t2);
        });
        
        Long optimal = 0;
        DisjointSet dsuOptimal(n+1);
        for (auto [u, v, w] : edges) {
            if (dsuOptimal.findParent(u) != dsuOptimal.findParent(v)) {
                dsuOptimal.unionNodes(u, v);
                optimal += w;
            }
        }

        Long queried = queryW;
        DisjointSet dsuQueried(n+1);
        dsuQueried.unionNodes(p, q);
        for (auto [u, v, w] : edges) {
            if (dsuQueried.findParent(u) != dsuQueried.findParent(v)) {
                dsuQueried.unionNodes(u, v);
                queried += w;
            }
        }
        
        std::cout << (queried == optimal ? "YES\n" : "NO\n");
    }

    return 0;
}