#include <iostream>
#include <algorithm>
#include <vector>

class DisjointSet {
private:
    std::vector<int> parent;

public:
    DisjointSet(int n) {
        parent.resize(n+1, -1);
    }

    int findRoot(int u) {
        if (parent[u] == -1) {
            return u;
        }
        return parent[u] = findRoot(parent[u]);
    }

    void mergeSet(int u, int v) {
        int uPar = findRoot(u);
        int vPar = findRoot(v);
        if (uPar != vPar) {
            parent[uPar] = vPar;
        }
    }
};

struct Edge {
    int start, end, width;

    bool operator<(const Edge& e) const {
        return width > e.width;
    }
};

int main() {
    int p, w, c, v;
    scanf("%d %d", &p, &w);
    scanf("%d %d", &c, &v);

    std::vector<Edge> edges(w);
    for (int i = 0; i < w; ++i) {
        scanf("%d %d %d", &edges[i].start, &edges[i].end, &edges[i].width);
    }

    std::sort(edges.begin(), edges.end());
    DisjointSet set(p);
    for (Edge& e : edges) {
        set.mergeSet(e.start, e.end);
        if (set.findRoot(c) == set.findRoot(v)) {
            printf("%d", e.width);
            break;
        }
    }

    return 0;
}