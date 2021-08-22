#include <iostream>
#include <algorithm>
#include <queue>

int n;
std::pair<int, int> points[200000];

bool isPossible(int minDist) {
    std::queue<std::pair<int, int>> q;
    int minY = 1e9, maxY = 0;
    for (int i = 0; i < n; ++i) {
        while (!q.empty() && q.front().first <= points[i].first-minDist) {
            auto prev = q.front();
            q.pop();
            minY = std::min(minY, prev.second);
            maxY = std::max(maxY, prev.second);
        }
        q.push(points[i]);
        if (minDist <= points[i].second-minY || minDist <= maxY-points[i].second) {
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &points[i].first, &points[i].second);
    }
    std::sort(points, points+n);

    int left = 0, right = 1e9+1;
    while (left+1 < right) {
        int med = (left+right) / 2;
        if (isPossible(med)) {
            left = med;
        } else {
            right = med;
        }
    }
    printf("%d", left);
    
    return 0;
}