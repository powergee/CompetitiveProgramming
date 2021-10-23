#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

bool areOnLine(std::pair<Long, Long> p1, std::pair<Long, Long> p2, std::pair<Long, Long> p3)
{
    Long result = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second
        - p1.second * p2.first - p2.second * p3.first - p3.second * p1.first;
    
    return result == 0;
}

int main() {
    int n;
    scanf("%d", &n);
    std::pair<Long, Long> points[n];

    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &points[i].first, &points[i].second);
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            for (int k = j+1; k < n; ++k) {
                if (!areOnLine(points[i], points[j], points[k])) {
                    ++result;
                }
            }
        }
    }

    printf("%d", result);

    return 0;
}