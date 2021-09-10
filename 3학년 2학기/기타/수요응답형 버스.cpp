#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

enum Kind { Bus = 0, Request = 1 };

struct Point {
    int x, y;
    Kind kind;

    bool operator<(const Point& p) const {
        if (y != p.y) {
            return y < p.y;
        } else if (x != p.x) {
            return x > p.x;
        }
        return kind < p.kind;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<Point> points(n+m);

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        points[i] = { a, b, Request };
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        points[n+i] = { a, b, Bus };
    }
    std::sort(points.begin(), points.end());

    int count = 0;
    std::map<int, int> busCount;
    for (auto p : points) {
        if (p.kind == Bus) {
            busCount[p.x]++;
        } else {
            auto it = busCount.lower_bound(p.x);
            if (it != busCount.end()) {
                ++count;
                it->second--;
                if (it->second == 0) {
                    busCount.erase(it);
                }
            }
        }
    }
    printf("%d", count);

    return 0;
}