#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <tuple>

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
    int n;
    scanf("%d", &n);

    std::vector<std::pair<double, double>> points(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        scanf("%lf %lf", &x, &y);
        points[i] = {x, y};
    }

    auto getDist = [](std::pair<double, double> p1, std::pair<double, double> p2) {
        return std::sqrt(std::pow(p1.first-p2.first, 2) + std::pow(p1.second-p2.second, 2));
    };

    std::vector<std::tuple<double, int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            double dist = getDist(points[i], points[j]);
            edges.emplace_back(dist, i, j);
        }
    }

    DisjointSet dsu(n);
    double sum = 0;
    std::sort(edges.begin(), edges.end());
    for (auto [dist, i, j] : edges) {
        if (dsu.findParent(i) != dsu.findParent(j)) {
            dsu.unionNodes(i, j);
            sum += dist;
        }
    }

    printf("%.10lf", sum);

    return 0;
}