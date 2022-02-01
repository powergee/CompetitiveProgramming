#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>

typedef long long Long;

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

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<Edge*> edges(m);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i] = new Edge(u, v, w);
    }

    std::sort(edges.begin(), edges.end(), [](Edge* e1, Edge* e2) -> bool {
        return e1->w < e2->w;
    });

    std::set<int> pivots = { 0 };
    for (int i = 0; i < m; ++i) {
        pivots.insert(edges[i]->w);
        for (int j = i+1; j < m; ++j) {
            int dist = edges[i]->w + edges[j]->w;
            pivots.insert(dist/2);
            pivots.insert(dist/2 + (dist%2));
        }
    }

    std::vector<std::pair<int, std::pair<Long, Long>>> mstVec;
    for (int p : pivots) {
        Long smallerSum = 0, biggerSum = 0;
        int smallerCount = 0, biggerCount = 0;
        DisjointSet dsu(n+1);
        std::sort(edges.begin(), edges.end(), [=](Edge* e1, Edge* e2) -> bool {
            auto abs1 = std::abs(e1->w-p);
            auto abs2 = std::abs(e2->w-p);
            if (abs1 != abs2) {
                return abs1 < abs2;
            }
            return e1->w > e2->w;
        });

        for (Edge* e : edges) {
            if (dsu.findParent(e->u) != dsu.findParent(e->v)) {
                dsu.unionNodes(e->u, e->v);
                if (e->w <= p) {
                    smallerSum += e->w;
                    smallerCount++;
                } else {
                    biggerSum += e->w;
                    biggerCount++;
                }
            }
        }
        mstVec.push_back(std::make_pair(p, std::make_pair(
            (smallerSum << 8) | smallerCount,
            (biggerSum << 8) | biggerCount
        )));
    }

    Long p, k, a, b, c;
    scanf("%lld %lld %lld %lld %lld", &p, &k, &a, &b, &c);
    
    int q;
    Long result = 0;
    for (int i = 0; i < k; ++i) {
        if (i < p) {
            scanf("%d", &q);
        } else {
            q = int((q*a + b) % c);
        }
        
        auto found = std::upper_bound(mstVec.begin(), mstVec.end(), std::make_pair(q, std::make_pair(INT64_MAX/2LL, INT64_MAX/2LL)));
        --found;

        auto mst = found->second;
        Long smallerCount = mst.first & ((1<<8) - 1);
        Long smallerSum = mst.first >> 8;
        Long biggerCount = mst.second & ((1<<8) - 1);
        Long biggerSum = mst.second >> 8;

        result ^= (q*smallerCount - smallerSum) + (biggerSum - q*biggerCount);
    }

    printf("%lld", result);

    return 0;
}