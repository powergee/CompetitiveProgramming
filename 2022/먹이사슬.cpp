#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    using Point = std::pair<int, int>;
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        int _, x, y;
        std::cin >> _ >> x >> y;
        points[i] = { x, y };
    }

    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());

    std::sort(points.begin(), points.end(), [](const Point& p, const Point& q) {
        if (p.second != q.second) {
            return p.second > q.second;
        }
        return p.first < q.first;
    });

    std::vector<int> lis;
    for (auto [x, y] : points) {
        auto found = std::upper_bound(lis.begin(), lis.end(), x);
        if (found == lis.end()) {
            lis.push_back(x);
        } else {
            *found = x;
        }
    }

    std::cout << lis.size();

    return 0;
}