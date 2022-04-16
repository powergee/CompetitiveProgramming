#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using Long = long long;
using Point = std::pair<Long, Long>;

Long getSquare(Long val) {
    return val * val;
}

Long getDist(Point p1, Point p2) {
    return getSquare(p1.first-p2.first) + getSquare(p1.second-p2.second);
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        Long x, y;
        scanf("%lld %lld", &x, &y);
        points[i] = {x, y};
    }
    std::sort(points.begin(), points.end());

    std::function<Long(int, int)> getMinDist = [&](int l, int r) -> Long {
        if (r-l == 0) {
            return INT32_MAX;
        } else if (r-l == 1) {
            return getDist(points[l], points[r]);
        }

        int m = (l+r)/2;
        Long dist = std::min(getMinDist(l, m), getMinDist(m+1, r));
        Long pivotX = (points[m].first + points[m+1].first) / 2;
        std::vector<Point> bucket;
        
        for (int i = l; i <= r; ++i) {
            if (getSquare(pivotX-points[i].first) < dist) {
                bucket.push_back(points[i]);
            }
        }
        std::sort(bucket.begin(), bucket.end(), [](Point p1, Point p2) { return p1.second < p2.second; });

        for (int i = 0; i < bucket.size(); ++i) {
            for (int j = i+1; j < bucket.size(); ++j) {
                if (dist <= getSquare(bucket[j].second - bucket[i].second)) {
                    break;
                }
                dist = std::min(dist, getDist(bucket[i], bucket[j]));
            }
        }

        return dist;
    };
    printf("%lld", getMinDist(0, n-1));

    return 0;
}