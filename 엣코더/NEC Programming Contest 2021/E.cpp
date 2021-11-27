#include <algorithm>
#include <cstdio>
#include <vector>

class DisjointSet
{
private:
    std::vector<int> parent;
    int comps;

public:
    DisjointSet(int count) {
        parent.resize(count);
        for (int i = 0; i < count; ++i)
            parent[i] = i;
        comps = count;
    }

    int findParent(int x) {
        if (x == parent[x])
            return x;
        
        return parent[x] = findParent(parent[x]);
    }

    void unionNodes(int x, int y) {
        int xPar = findParent(x);
        int yPar = findParent(y);
        if (xPar != yPar) {
            --comps;
        }

        parent[xPar] = yPar;
    }

    int countComps() {
        return comps;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        edges[i] = { u-1, v-1 };
    }
    
    auto getMinVertex = [](std::pair<int, int> e) -> int {
        return std::min(e.first, e.second);
    };

    std::sort(edges.begin(), edges.end(), [&](std::pair<int, int> e1, std::pair<int, int> e2) -> bool {
        return getMinVertex(e1) < getMinVertex(e2);
    });

    DisjointSet dsu(n);
    std::vector<int> answer(n);
    for (int i = n-1; i >= 0; --i) {
        answer[i] = dsu.countComps()-(i+1);
        while (!edges.empty() && i <= getMinVertex(edges.back())) {
            dsu.unionNodes(edges.back().first, edges.back().second);
            edges.pop_back();
        }
    }

    for (int ans : answer) {
        printf("%d\n", ans);
    }

    return 0;
}
