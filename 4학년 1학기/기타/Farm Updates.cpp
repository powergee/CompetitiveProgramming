#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

class DisjointSet {
private:
    std::vector<int> parent, sum;
    std::vector<std::vector<int>> members;
public:
    DisjointSet(int count) {
        parent.resize(count);
        sum.resize(count, 1);
        members.resize(count);
        for (int i = 0; i < count; ++i) {
            parent[i] = i;
            members[i].push_back(i);
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
        if (xPar == yPar) {
            return;
        }
        if (members[xPar].size() > members[yPar].size()) {
            std::swap(xPar, yPar);
        }
        parent[xPar] = yPar;
        sum[yPar] += sum[xPar];
        sum[xPar] = 0;
        members[yPar].insert(members[yPar].end(), members[xPar].begin(), members[xPar].end());
        members[xPar].clear();
    }

    int getSum(int x) {
        return sum[findParent(x)];
    }

    void addValue(int x, int v) {
        sum[findParent(x)] += v;
    }

    std::vector<int>& getMembers(int x) {
        return members[findParent(x)];
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    DisjointSet dsu(n+1);
    std::vector<std::tuple<char, int, int>> queries(m);
    std::vector<std::pair<int, int>> edges;
    std::vector<int> removedAt;
    for (int i = 0; i < m; ++i) {
        char com[2];
        std::cin >> com;
        if (com[0] == 'A') {
            int x, y;
            std::cin >> x >> y;
            queries[i] = { 'A', x, y };
            edges.emplace_back(x, y);
            removedAt.push_back(INT32_MAX);
        } else if (com[0] == 'D') {
            int x;
            std::cin >> x;
            queries[i] = { 'D', x, -1 };
            dsu.addValue(x, -1);
        } else {
            int e;
            std::cin >> e;
            queries[i] = { 'R', e-1, -1 };
            removedAt[e-1] = i;
        }
    }

    std::vector<int> edgesByLifetime(edges.size());
    for (int i = 0; i < edges.size(); ++i) {
        edgesByLifetime[i] = i;
    }
    std::sort(edgesByLifetime.begin(), edgesByLifetime.end(), [&](int e1, int e2) {
        return removedAt[e1] > removedAt[e2];
    });

    for (int v = 1; v <= n; ++v) {
        if (dsu.getSum(v) == 1) {
            dsu.getMembers(v).clear();
        }
    }

    int time = m-1;
    std::vector<int> answer(n+1, m);
    for (int i = 0; i < edgesByLifetime.size(); ++i) {
        int removedTime = removedAt[edgesByLifetime[i]];
        while (time > removedTime) {
            auto [com, x, y] = queries[time];
            if (com == 'D') {
                if (dsu.getSum(x) == 0) {
                    for (int v : dsu.getMembers(x)) {
                        answer[v] = time;
                    }
                    dsu.getMembers(x).clear();
                }
                dsu.addValue(x, 1);
            }
            --time;
        }

        auto [u, v] = edges[edgesByLifetime[i]];
        if (removedTime != INT32_MAX) {
            int left = dsu.getSum(u);
            int right = dsu.getSum(v);
            if ((left == 0) != (right == 0)) {
                int x = (left == 0 ? u : v);
                for (int y : dsu.getMembers(x)) {
                    answer[y] = time;
                }
                dsu.getMembers(x).clear();
            }
        }
        dsu.unionNodes(u, v);
    }

    while (time >= 0) {
        auto [com, x, y] = queries[time];
        if (com == 'D') {
            if (dsu.getSum(x) == 0) {
                for (int v : dsu.getMembers(x)) {
                    answer[v] = time;
                }
                dsu.getMembers(x).clear();
            }
            dsu.addValue(x, 1);
        }
        --time;
    }

    for (int v = 1; v <= n; ++v) {
        std::cout << answer[v] << "\n";
    }

    return 0;
}