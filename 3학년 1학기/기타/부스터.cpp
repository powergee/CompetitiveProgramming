#include <iostream>
#include <algorithm>
#include <vector>

struct Point {
    int x, y, index;
};

struct PointPair {
    Point *p1, *p2;

    int getDist() {
        return std::min(std::abs(p1->x-p2->x), std::abs(p1->y-p2->y));
    }
};

struct Query {
    int start, end, hp, index;
};

int parents[250000];

int findParent(int v) {
    int p = parents[v];
    if (p == v) {
        return p;
    } else {
        return parents[v] = findParent(p);
    }
}

void unionSet(int u, int v) {
    int uPar = findParent(u);
    int vPar = findParent(v);
    if (uPar != vPar) {
        parents[uPar] = vPar;
    }
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<Point> points(n);
    std::vector<Point*> xSorted, ySorted;

    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        points.push_back({x, y, i});
        xSorted.push_back(&points.back());
        ySorted.push_back(&points.back());
        parents[i] = i;
    }

    std::sort(xSorted.begin(), xSorted.end(), [](auto p1, auto p2) -> bool {
        return p1->x < p2->x;
    });
    std::sort(ySorted.begin(), ySorted.end(), [](auto p1, auto p2) -> bool {
        return p1->y < p2->y;
    });

    std::vector<PointPair> edges;
    for (int i = 0; i < n-1; ++i) {
        edges.push_back({xSorted[i], xSorted[i+1]});
        edges.push_back({ySorted[i], ySorted[i+1]});
    }

    std::sort(edges.begin(), edges.end(), [](auto e1, auto e2) -> bool {
        return e1.getDist() > e2.getDist();
    });

    std::vector<Query> queries;
    for (int i = 0; i < q; ++i) {
        int s, e, h;
        scanf("%d %d %d", &s, &e, &h);
        queries.push_back({s-1, e-1, h, i});
    }

    std::sort(queries.begin(), queries.end(), [](auto q1, auto q2) -> bool {
        return q1.hp < q2.hp;
    });

    std::vector<bool> answers(q);
    for (Query qr : queries) {
        while (!edges.empty() && edges.back().getDist() <= qr.hp) {
            unionSet(edges.back().p1->index, edges.back().p2->index);
            edges.pop_back();
        }

        if (findParent(qr.start) == findParent(qr.end)) {
            answers[qr.index] = true;
        } else {
            answers[qr.index] = false;
        }
    }

    for (int ans : answers) {
        printf(ans ? "YES\n" : "NO\n");
    }

    return 0;
}