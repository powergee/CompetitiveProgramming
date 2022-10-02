#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &points[i].first);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &points[i].second);
    }

    std::vector<double> fromLeft(n, 0), fromRight(n, 0);
    for (int i = 1; i < n; ++i) {
        double x = points[i-1].first - points[i].first;
        double y = points[i-1].second - points[i].second;
        double mult = 2;
        if (points[i-1].second < points[i].second) {
            mult = 3;
        } else if (points[i-1].second > points[i].second) {
            mult = 1;
        }
        fromLeft[i] = fromLeft[i-1] + mult * std::sqrt(x*x+y*y);
    }
    for (int i = n-2; i >= 0; --i) {
        double x = points[i].first - points[i+1].first;
        double y = points[i].second - points[i+1].second;
        double mult = 2;
        if (points[i+1].second < points[i].second) {
            mult = 3;
        } else if (points[i+1].second > points[i].second) {
            mult = 1;
        }
        fromRight[i] = fromRight[i+1] + mult * std::sqrt(x*x+y*y);
    }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;
        r--;

        double answer = 0;
        if (l < r) {
            answer = fromLeft[r] - fromLeft[l];
        } else {
            answer = fromRight[r] - fromRight[l];
        }

        printf("%.10lf\n", answer);
    }

    return 0;
}