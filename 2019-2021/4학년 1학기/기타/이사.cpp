#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &points[i].first, &points[i].second);
    }

    auto getDist = [&](int i, int j) {
        auto p1 = points[i];
        auto p2 = points[j];
        int d1 = p1.first-p2.first;
        int d2 = p1.second-p2.second;
        return d1*d1 + d2*d2;
    };
    
    int minIdx = -1, minDist = INT32_MAX;
    for (int i = 0; i < n; ++i) {
        int farthest = i;
        for (int j = 0; j < n; ++j) {
            if (getDist(i, farthest) < getDist(i, j)) {
                farthest = j;
            }
        }
        int dist = getDist(i, farthest);
        if (dist < minDist) {
            minDist = dist;
            minIdx = i;
        }
    }

    printf("%d %d\n", points[minIdx].first, points[minIdx].second);

    return 0;
}