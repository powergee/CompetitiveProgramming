#include <iostream>
#include <vector>

std::pair<int, int> getMinGap(std::vector<int> points) {
    int minGap = INT32_MAX;
    int minGapIndex = 0;
    for (int i = 0; i+1 < points.size(); ++i) {
        int currGap = points[i+1] - points[i] - 1;
        if (currGap < minGap) {
            minGap = currGap;
            minGapIndex = i;
        }
    }
    return {minGap, minGapIndex};
}

std::vector<int> moveBack(std::vector<int> points, int idx, int d) {
    points[idx] = d;
    for (int i = idx; i+1 < points.size(); ++i) {
        if (points[i] > points[i+1]) {
            std::swap(points[i], points[i+1]);
        }
    }
    return points;
}

std::vector<int> moveToLargestGap(std::vector<int> points, int idx) {
    if (points.size() <= 1) {
        return points;
    }
    points.erase(points.begin()+idx);
    int maxGap = INT32_MIN;
    int maxGapIndex = 0;
    for (int i = 0; i+1 < points.size(); ++i) {
        int currGap = points[i+1] - points[i];
        if (maxGap < currGap) {
            maxGap = currGap;
            maxGapIndex = i;
        }
    }
    int newPos = (points[maxGapIndex+1] + points[maxGapIndex]) / 2;
    points.insert(points.begin()+maxGapIndex+1, newPos);
    return points;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, d;
        scanf("%d %d", &n, &d);

        std::vector<int> points(n+1);
        points[0] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &points[i]);
        }

        auto [answer, cand1] = getMinGap(points);
        int cand2 = cand1+1;
        
        answer = std::max(answer, getMinGap(moveBack(points, cand1, d)).first);
        answer = std::max(answer, getMinGap(moveToLargestGap(points, cand1)).first);
        answer = std::max(answer, getMinGap(moveBack(points, cand2, d)).first);
        answer = std::max(answer, getMinGap(moveToLargestGap(points, cand2)).first);

        printf("%d\n", answer);
    }

    return 0;
}