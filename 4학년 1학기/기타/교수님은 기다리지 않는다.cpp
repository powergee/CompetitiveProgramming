#include <iostream>
#include <vector>

class DisjointSet {
private:
    std::vector<std::pair<int, int>> parent;
public:
    DisjointSet(int count) {
        parent.resize(count);
        for (int i = 0; i < count; ++i) {
            parent[i] = { i, 0 };
        }
    }

    std::pair<int, int> findParent(int x) {
        if (x == parent[x].first) {
            return parent[x];
        }
        auto sub = findParent(parent[x].first);
        parent[x] = { sub.first, sub.second+parent[x].second };
        return parent[x];
    }

    void unionNodes(int x, int y, int cost) {
        auto xPar = findParent(x);
        auto yPar = findParent(y);

        parent[xPar.first] = { yPar.first, yPar.second-xPar.second-cost };
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    while ((std::cin >> n >> m), n != 0) {
        DisjointSet dsu(n+1);
        while (m--) {
            char kind[2];
            std::cin >> kind;
            if (kind[0] == '!') {
                int a, b, w;
                std::cin >> a >> b >> w;
                dsu.unionNodes(a, b, w);
            } else {
                int a, b;
                std::cin >> a >> b;
                auto aPar = dsu.findParent(a);
                auto bPar = dsu.findParent(b);
                if (aPar.first == bPar.first) {
                    std::cout << bPar.second-aPar.second << "\n";
                } else {
                    std::cout << "UNKNOWN\n";
                }
            }
        }
    }

    return 0;
}