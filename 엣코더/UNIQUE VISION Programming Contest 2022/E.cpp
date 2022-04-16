#include <iostream>
#include <vector>
#include <functional>
#include <set>
#include <tuple>
#include <numeric>

using Long = long long;
using Line = std::tuple<Long, Long, Long>;

bool isOnLine(Line line, Long x, Long y) {
    auto [xCoeff, yCoeff, sum] = line;
    return xCoeff * x + yCoeff * y == sum;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if (k == 1) {
        printf("Infinity");
        return 0;
    }

    std::vector<std::pair<Long, Long>> points(n);
    std::set<Long> xLines, yLines;
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &points[i].first, &points[i].second);
        xLines.insert(points[i].second);
        yLines.insert(points[i].first);
    }
    int answer = 0;

    for (Long xLine : xLines) {
        int count = 0;
        for (auto [x, y] : points) {
            if (y == xLine) {
                ++count;
            }
        }
        if (count >= k) {
            ++answer;
        }
    }
    for (Long yLine : yLines) {
        int count = 0;
        for (auto [x, y] : points) {
            if (x == yLine) {
                ++count;
            }
        }
        if (count >= k) {
            ++answer;
        }
    }
    
    std::set<Line> used;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            auto [x1, y1] = points[i];
            auto [x2, y2] = points[j];
            Long xCoeff = y2-y1;
            Long yCoeff = -(x2-x1);
            Long sum = -y1*(x2-x1) + x1*(y2-y1);
            if (xCoeff == 0 || yCoeff == 0) {
                continue;
            }

            if (xCoeff < 0) {
                xCoeff = -xCoeff;
                yCoeff = -yCoeff;
                sum = -sum;
            }

            std::vector<Long> abs;
            if (xCoeff != 0) {
                abs.push_back(std::abs(xCoeff));
            }
            if (yCoeff != 0) {
                abs.push_back(std::abs(yCoeff));
            }
            if (sum != 0) {
                abs.push_back(std::abs(sum));
            }
            if (abs.size()) {
                Long v = abs.front();
                for (int i = 1; i < abs.size(); ++i) {
                    v = std::gcd(v, abs[i]);
                }
                xCoeff /= v;
                yCoeff /= v;
                sum /= v;
            }

            Line lineInfo = { xCoeff, yCoeff, sum };
            if (used.count(lineInfo)) {
                continue;
            }
            used.insert(lineInfo);
            int count = 0;
            for (auto [x, y] : points) {
                if (isOnLine(lineInfo, x, y)) {
                    ++count;
                }
            }
            if (count >= k) {
                ++answer;
            }
        }
    }

    printf("%d", answer);

    return 0;
}