#include <iostream>
#include <vector>
#include <algorithm>

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

        if (xPar != yPar) {
            parent[xPar] = yPar;
        }
    }
};

int COUNT = 0;
struct Edge {
    int u, v, c;
    bool isVirtual;
    int index;
    bool isUsed = false;

    Edge(int u, int v, int c, bool isVirtual): u(u), v(v), c(c), isVirtual(isVirtual) {
        index = COUNT++;
    };
};

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    std::vector<Edge> edges;

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        edges.emplace_back(a, b, c, false);
    }

    for (int i = 0; i < q; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        edges.emplace_back(a, b, c, true);
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
        return e1.c < e2.c;
    });

    DisjointSet dsu(n+1);
    for (Edge& e : edges) {
        if (e.isVirtual) {
            if (dsu.findParent(e.u) == dsu.findParent(e.v)) {
                e.isUsed = false;
            } else {
                e.isUsed = true;
            }
        } else {
            dsu.unionNodes(e.u, e.v);
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
        return e1.index < e2.index;
    });

    for (Edge& e : edges) {
        if (e.isVirtual) {
            printf(e.isUsed ? "Yes\n" : "No\n");
        }
    }

    return 0;
}