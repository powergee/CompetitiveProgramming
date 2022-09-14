#include <iostream>
#include <vector>
#include <map>

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

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    std::vector<int> fee(n+1);
    for (int v = 1; v <= n; ++v) {
        scanf("%d", &fee[v]);
    }

    DisjointSet set(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        set.mergeSet(u, v);
    }

    std::map<int, std::pair<int, int>> setInfo;
    for (int v = 1; v <= n; ++v) {
        int root = set.findRoot(v);
        if (setInfo.find(root) == setInfo.end()) {
            setInfo[root] = { fee[v], 1 };
        } else {
            auto prev = setInfo[root];
            setInfo[root] = { std::min(fee[v], prev.first), prev.second+1 };
        }
    }

    int total = 0;
    for (auto info : setInfo) {
        total += info.second.first;
    }

    if (total <= k) {
        printf("%d", total);
    } else {
        printf("Oh no");
    }

    return 0;
}