#include <cstdio>
#include <vector>

class DisjointSet
{
private:
    std::vector<int> parent;
public:
    DisjointSet(int count)
    {
        parent.resize(count);
        for (int i = 0; i < count; ++i)
            parent[i] = i;
    }

    int findParent(int x)
    {
        if (x == parent[x])
            return x;
        
        return parent[x] = findParent(parent[x]);
    }

    void unionNodes(int x, int y)
    {
        int xPar = findParent(x);
        int yPar = findParent(y);

        parent[xPar] = yPar;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    bool yes = true;
    DisjointSet dsu(n+1);
    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (dsu.findParent(a) == dsu.findParent(b) ||
            graph[a].size() >= 2 || graph[b].size() >= 2) {
            yes = false;
            break;
        }
        dsu.unionNodes(a, b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    printf(yes ? "Yes" : "No");

    return 0;
}
