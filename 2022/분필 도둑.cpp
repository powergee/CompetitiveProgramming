#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <numeric>

class DisjointSet {
private:
    std::vector<int> parent, size;
public:
    DisjointSet(int count) {
        parent.resize(count);
        size.resize(count, 1);
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
        if (xPar != yPar) {
            parent[xPar] = yPar;
            size[yPar] += size[xPar];
        }
    }

    int getSize(int x) {
        return size[findParent(x)];
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<int> chalk(n+1);
    std::map<int, std::vector<int>, std::greater<int>> verByChalk;
    for (int i = 1; i <= n; ++i) {
        std::cin >> chalk[i];
        verByChalk[chalk[i]].push_back(i);
    }

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    DisjointSet dsu(n+1);
    std::vector<bool> added(n+1, false);
    long long answer = 0;
    for (const auto& [ch, vs] : verByChalk) {
        for (int v : vs) {
            added[v] = true;
            for (int next : graph[v]) {
                if (added[next]) {
                    dsu.unionNodes(v, next);
                }
            }
            answer = std::max(answer, 1LL*dsu.getSize(v)*ch);
        }
    }

    std::cout << answer << "\n";

    return 0;
}