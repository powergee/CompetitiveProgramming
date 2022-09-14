#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

struct Point {
    Long x, y;
    int index;

    Point(Long x, Long y, int index) : x(x), y(y), index(index) {}
    Point(Long x, Long y) : Point(x, y, -1) {}

    Long getDist(const Point& p) const {
        return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
    }

    bool operator<(const Point& p) const {
        if (x == p.x) {
            return y < p.y;
        }
        return x < p.x;
    }
};

Long getCCW(const Point& p1, const Point& p2, const Point& p3) {
    return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y
         - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x;
}

void tryToPush(const Point& p, std::vector<Point>& hull) {
    #define PREV2 hull[hull.size() - 2]
    #define PREV1 hull[hull.size() - 1]
    #define LAST_CCW (getCCW(PREV2, PREV1, p))

    while (LAST_CCW < 0) {
        hull.pop_back();
    }
    if (LAST_CCW > 0) {
        hull.push_back(p);
    } else if (LAST_CCW == 0 && PREV2.getDist(PREV1) < PREV2.getDist(p)) {
        PREV1 = p;
    }
}

std::vector<Point> GetConvexHull(std::vector<Point>& points) {
    std::vector<Point> result;
    Point anglePivot = *std::min_element(points.begin(), points.end());
    std::sort(points.begin(), points.end(), [&](auto p1, auto p2) -> bool {
        Long ccw = getCCW(anglePivot, p1, p2);
        if (ccw == 0) {
            return anglePivot.getDist(p1) < anglePivot.getDist(p2);
        }
        return ccw > 0;
    });

    result.push_back(points[0]);
    result.push_back(points[1]);
    for (int i = 2; i < points.size(); ++i) {
        tryToPush(points[i], result);
    }
    tryToPush(points[0], result);
    result.pop_back();

    if (result.size() == 1 && !(result[0].x == points.back().x && result[0].y == points.back().y)) {
        result.push_back(points.back());
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    std::vector<Point> points;

    for (int i = 0; i < n; ++i) {
        Long x, y;
        scanf("%lld %lld", &x, &y);
        points.emplace_back(x, y);
    }
    std::vector<Point> hull = GetConvexHull(points);
    printf("%d\n", (int)hull.size());
    return 0;
}