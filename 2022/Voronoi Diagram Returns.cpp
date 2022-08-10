#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].first >> points[i].second;
    }

    int minDist = INT32_MAX;
    std::vector<int> answer;
    answer.reserve(n);
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        for (int i = 0; i < n; ++i) {
            int xDiff = points[i].first-x;
            int yDiff = points[i].second-y;
            int dist = xDiff*xDiff + yDiff*yDiff;
            if (dist < minDist) {
                minDist = dist;
                answer.resize(0);
                answer.push_back(i+1);
            } else if (dist == minDist) {
                answer.push_back(i+1);
            }
        }

        if (answer.size() == 1) {
            std::cout << "REGION " << answer[0] << "\n";
        } else if (answer.size() == 2) {
            std::cout << "LINE " << answer[0] << " " << answer[1] << "\n";
        } else {
            std::cout << "POINT" << "\n";
        }
        answer.resize(0);
        minDist = INT32_MAX;
    }

    return 0;
}