#include <iostream>
#include <tuple>
#include <vector>

using Edge = std::tuple<int, int, int>;

class DisjointSet {
private:
    std::vector<int> parent;
public:
    DisjointSet(int count) {
        parent.resize(count);
        for (int i = 0; i < count; ++i) {
            parent[i] = i;
        }
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
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        
        std::vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            edges.emplace_back(u, v, c);
        }

        auto isConnected = [&](int mask) -> bool {
            DisjointSet dsu(n+1);
            for (auto[u, v, c] : edges) {
                if ((mask & c) == c) {
                    dsu.unionNodes(u, v);
                }
            }
            for (int i = 2; i <= n; ++i) {
                if (dsu.findParent(1) != dsu.findParent(i)) {
                    return false;
                }
            }
            return true;
        };

        int answer = 0x7FFFFFFF;
        for (int e = 30; e >= 0; --e) {
            int bit = (1<<e);
            if (isConnected(answer-bit)) {
                answer -= bit;
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}