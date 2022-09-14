#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int f, r, n;
        scanf("%d %d %d", &f, &r, &n);

        std::vector<std::vector<int>> points(f+1);
        for (int i = 0; i < n; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            points[a].push_back(b);
        }

        for (int i = 0; i <= f; ++i) {
            std::sort(points[i].begin(), points[i].end());
        }

        int answer = 2*f + r + 1;
        for (int i = 0; i <= f; ++i) {
            if (points[i].empty()) continue;

            int curr = std::min(2*points[i].back(), 2*(r-points[i].front()+1));
            for (int j = 0; j+1 < points[i].size(); ++j) {
                curr = std::min(curr, 2*points[i][j] + 2*(r-points[i][j+1]+1));
            }
            answer += curr;
        }
        
        printf("%d\n", answer);
    }

    return 0;
}