#include <iostream>
#include <vector>
#include <cmath>

using Long = long long;
using Point = std::pair<Long, Long>;

Long getDoubleSize(Point& p1, Point& p2, Point& p3) {
    auto x1 = p1.first, y1 = p1.second;
    auto x2 = p2.first, y2 = p2.second;
    auto x3 = p3.first, y3 = p3.second;

    return x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y1 - x1*y3;
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

    Long sum = 0;
    for (int i = 1; i < n-1; ++i) {
        sum += getDoubleSize(points[0], points[i], points[i+1]);
    }
    sum = std::abs(sum);
    printf("%lld", sum/2);
    if (sum % 2) {
        printf(".5");
    } else {
        printf(".0");
    }

    return 0;
}