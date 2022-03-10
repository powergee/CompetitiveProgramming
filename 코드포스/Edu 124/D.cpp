#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <map>

typedef long long Long;

struct Point {
    int r, c, dist;
    int nearestR, nearestC;
};

bool compareByColumn(Point* p1, Point* p2) {
    return p1->c < p2->c;
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Point> points(n);
    std::map<int, std::vector<Point*>> rows;

    for (int i = 0; i < n; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        points[i] = { r, c, INT32_MAX/2, 0, 0 };
        rows[r].push_back(&points[i]);
    }

    for (auto& [r, row] : rows) {
        std::sort(row.begin(), row.end(), compareByColumn);
    }

    auto findPoint = [&](int r, int c) -> Point* {
        auto found = rows.find(r);
        if (found == rows.end()) {
            return nullptr;
        }
        Point pivot = { r, c, 0, 0, 0 };
        auto foundPoint = std::lower_bound(found->second.begin(), found->second.end(), &pivot, compareByColumn);
        if (foundPoint == found->second.end() || (*foundPoint)->r != r || (*foundPoint)->c != c) {
            return nullptr;
        }
        return *foundPoint;
    };

    auto relaxPoint = [&](Point* p, int pivotR, int pivotC) {
        Point* found = findPoint(pivotR, pivotC);
        if (found == nullptr) {
            p->dist = 1;
            p->nearestR = pivotR;
            p->nearestC = pivotC;
        } else if (found->dist+1 < p->dist) {
            p->dist = found->dist+1;
            p->nearestR = found->nearestR;
            p->nearestC = found->nearestC;
        }
    };

    for (auto& [r, row] : rows) {
        // down
        for (Point* p : row) {
            relaxPoint(p, r-1, p->c);
        }
        // left
        for (Point* p : row) {
            relaxPoint(p, r, p->c-1);
        }
        // right
        for (auto it = row.rbegin(); it != row.rend(); ++it) {
            Point* p = *it;
            relaxPoint(p, r, p->c+1);
        }
    }

    for (auto it = rows.rbegin(); it != rows.rend(); ++it) {
        auto& [r, row] = *it;
        // up
        for (Point* p : row) {
            relaxPoint(p, r+1, p->c);
        }
        // left
        for (Point* p : row) {
            relaxPoint(p, r, p->c-1);
        }
        // right
        for (auto jt = row.rbegin(); jt != row.rend(); ++jt) {
            Point* p = *jt;
            relaxPoint(p, r, p->c+1);
        }
    }

    for (Point& p : points) {
        printf("%d %d\n", p.nearestR, p.nearestC);
    }

    return 0;
}