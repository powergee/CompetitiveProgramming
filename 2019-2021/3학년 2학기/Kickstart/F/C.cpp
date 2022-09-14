#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef long long Long;
using Point = std::pair<Long, Long>;
using Shape = std::vector<Point>;

Long CCW(const Point& p1, const Point& p2, const Point& p3) {
    return p1.first * p2.second + p2.first * p3.second + p3.first * p1.second
         - p1.second * p2.first - p2.second * p3.first - p3.second * p1.first;
}

double getDist(Point& p1, Point& p2) {
    return std::sqrt(std::pow(p1.first-p2.first, 2) + std::pow(p1.second-p2.second, 2));
}

void sortByCCW(Shape& s) {
    Point anglePivot = *std::min_element(s.begin(), s.end());
    std::sort(s.begin(), s.end(), [&](auto p1, auto p2) -> bool {
        Long ccw = CCW(anglePivot, p1, p2);
        if (ccw == 0) {
            return getDist(anglePivot, p1) < getDist(anglePivot, p2);
        }
        return ccw > 0;
    });
}

double getPerimeter(Shape s) {
    sortByCCW(s);
    double sum = 0;
    for (int i = 0; i < s.size(); ++i) {
        sum += getDist(s[i], s[(i+1)%s.size()]);
    }
    return sum;
}

bool isOnBorder(Shape s, Point& p) {
    for (int i = 0; i < s.size(); ++i) {
        int j = (i+1) % s.size();
        int minX = std::min(s[i].first, s[j].first);
        int maxX = std::max(s[i].first, s[j].first);
        int minY = std::min(s[i].second, s[j].second);
        int maxY = std::max(s[i].second, s[j].second);

        if (minX <= p.first && p.first <= maxX &&
            minY <= p.second && p.second <= maxY) {
            if (p.first == minX && p.first == maxX) {
                return true;
            }
            double r1 = double(p.second - s[i].second) / (p.first - s[i].first);
            double r2 = double(p.second - s[j].second) / (p.first - s[j].first);
            if (std::abs(r1) == std::abs(r2)) {
                return true;
            }
        }
    }
    return false;
}

bool isIn(Shape s, Point& p) {
    sortByCCW(s);
    for (int i = 0; i < s.size(); ++i) {
        if (CCW(s[i], s[(i+1)%s.size()], p) <= 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);;

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);

        int n;
        std::cin >> n;

        std::vector<Point> whStars;
        Point blStar;

        for (int i = 0; i < n; ++i) {
            int x, y;
            std::cin >> x >> y;
            whStars.emplace_back(x, y);
        }
        std::cin >> blStar.first >> blStar.second;

        bool possible = false;
        double answer = INT64_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                for (int k = j+1; k < n; ++k) {
                    Shape sh = { whStars[i], whStars[j], whStars[k] };
                    if (isIn(sh, blStar)) {
                        possible = true;
                        answer = std::min(answer, getPerimeter(sh));
                    } else if (isOnBorder(sh, blStar)) {
                        for (int l = k+1; l < n; ++l) {
                            if (!isIn(sh, whStars[l]) && !isOnBorder(sh, whStars[l])) {
                                sh.push_back(whStars[l]);
                                if (isIn(sh, blStar)) {
                                    possible = true;
                                    answer = std::min(answer, getPerimeter(sh));
                                }
                                sh.pop_back();
                            }
                        }
                    }
                }
            }
        }

        if (possible) {
            printf("%.10lf\n", answer);
        } else {
            printf("IMPOSSIBLE\n");
        }
    }

    return 0;
}