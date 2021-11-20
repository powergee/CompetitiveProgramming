#include <cstdio>
#include <vector>

typedef long long Long;

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
    std::vector<Long> values(1<<20, -1);
    DisjointSet dsu(1<<20);

    auto findBoundary = [&](int pivot, int l, int r) -> int {
        while (l < r) {
            int m = (l+r)/2;
            if (dsu.findParent(pivot) == dsu.findParent(m)) {
                l = m+1;
            } else {
                r = m;
            }
        }
        return l;
    };

    auto connectNeighbors = [&](int p) -> void {
        int left = p-1;
        if (left >= 0 && values[left] != -1) {
            dsu.unionNodes(left, p);
        }
        int right = p+1;
        if (right < (1<<20) && values[right] != -1) {
            dsu.unionNodes(p, right);
        }
    };

    int q;
    scanf("%d", &q);

    while (q--) {
        int t;
        Long x;
        scanf("%d %lld", &t, &x);

        if (t == 1) {
            int p = x % (1<<20);
            if (values[p] == -1) {
                values[p] = x;
                connectNeighbors(p);
            } else if (dsu.findParent(p) == dsu.findParent((1<<20)-1)) {
                if (values[0] == -1) {
                    values[0] = x;
                    connectNeighbors(0);
                } else {
                    int bound = findBoundary(0, 0, p-1);
                    values[bound] = x;
                    connectNeighbors(bound);
                }
            } else {
                int bound = findBoundary(p, p, (1<<20)-1);
                values[bound] = x;
                connectNeighbors(bound);
            }
        } else {
            printf("%lld\n", values[x%(1<<20)]);
        }
    }

    return 0;
}
