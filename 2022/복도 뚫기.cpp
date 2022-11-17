#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <tuple>
#include <cmath>
#include <limits>
#include <iomanip>

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
        int w, n;
        std::cin >> w >> n;
        
        std::vector<std::tuple<int, int, double>> circle(n);
        for (int i = 0; i < n; ++i) {
            int x, y, r;
            std::cin >> x >> y >> r;
            circle[i] = { x, y, double(r) };
        }

        const int LEFT_WALL = n;
        const int RIGHT_WALL = n+1;
        std::vector<std::tuple<int, int, double>> edges;
        edges.emplace_back(LEFT_WALL, RIGHT_WALL, w);
        
        for (int i = 0; i < n; ++i) {
            auto [xi, yi, ri] = circle[i];
            for (int j = i+1; j < n; ++j) {
                auto [xj, yj, rj] = circle[j];
                double dist = std::sqrt(std::pow(xi-xj, 2) + std::pow(yi-yj, 2)) - ri - rj;
                edges.emplace_back(i, j, dist);
            }
            edges.emplace_back(i, LEFT_WALL, xi-ri);
            edges.emplace_back(i, RIGHT_WALL, w-(xi+ri));
        }

        std::sort(edges.begin(), edges.end(), [](auto e1, auto e2) {
            return std::get<2>(e1) < std::get<2>(e2);
        });

        DisjointSet dsu(n+2);
        double largest = std::numeric_limits<double>::min();
        for (auto [u, v, cost] : edges) {
            if (dsu.findParent(u) != dsu.findParent(v)) {
                dsu.unionNodes(u, v);
                largest = cost;
            }
            if (dsu.findParent(LEFT_WALL) == dsu.findParent(RIGHT_WALL)) {
                break;
            }
        }
        if (largest < 0) {
            std::cout << "0\n";
        } else {
            std::cout << std::fixed << std::setprecision(10) << largest/2 << "\n";
        }
    }

    return 0;
}