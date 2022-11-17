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
    int width, height;
    std::cin >> width >> height;
    
    int k;
    std::cin >> k;

    std::vector<std::pair<int, int>> poll(k);
    for (int i = 0; i < k; ++i) {
        int x, y;
        std::cin >> x >> y;
        poll[i] = { x, y };
    }

    const int UPPER_WALL = k;
    const int LOWER_WALL = k+1;
    std::vector<std::tuple<int, int, double>> edges;
    for (int i = 0; i < k; ++i) {
        auto [xi, yi] = poll[i];
        for (int j = i+1; j < k; ++j) {
            auto [xj, yj] = poll[j];
            double dist = std::sqrt(std::pow(xi-xj, 2) + std::pow(yi-yj, 2));
            edges.emplace_back(i, j, dist);
        }
        edges.emplace_back(i, UPPER_WALL, height-yi);
        edges.emplace_back(i, LOWER_WALL, yi);
    }

    std::sort(edges.begin(), edges.end(), [](auto e1, auto e2) {
        return std::get<2>(e1) < std::get<2>(e2);
    });

    DisjointSet dsu(k+2);
    double largest = std::numeric_limits<double>::min();
    for (auto [u, v, c] : edges) {
        if (dsu.findParent(u) != dsu.findParent(v)) {
            dsu.unionNodes(u, v);
            largest = c;
        }
        if (dsu.findParent(UPPER_WALL) == dsu.findParent(LOWER_WALL)) {
            break;
        }
    }
    if (largest < 0) {
        std::cout << "0\n";
    } else {
        std::cout << std::fixed << std::setprecision(8) << largest/2 << "\n";
    }

    return 0;
}