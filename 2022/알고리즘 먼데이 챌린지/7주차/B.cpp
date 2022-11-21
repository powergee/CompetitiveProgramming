#include <iostream>
#include <vector>
#include <numeric>

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
    int n, m;
    std::cin >> n >> m;

    DisjointSet dsu(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        dsu.unionNodes(u, v);
    }

    int answer = 0;
    for (int v = 1; v <= n; ++v) {
        if (dsu.findParent(1) == dsu.findParent(v)) {
            ++answer;
        }
    }
    std::cout << answer;

    return 0;
}