#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        std::vector<int> dists;
        std::pair<int, int> POINTS[] {
            { 0, 0 },
            { 0, m-1 },
            { n-1, 0 },
            { n-1, m-1 },
        };
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int maxDist = 0;
                for(int k = 0; k < 4; ++k) {
                    maxDist = std::max(maxDist, std::abs(POINTS[k].first-i) + std::abs(POINTS[k].second-j));
                }
                dists.push_back(maxDist);
            }
        }

        std::sort(dists.begin(), dists.end());
        for (int d : dists) {
            printf("%d ", d);
        }
        printf("\n");
    }

    return 0;
}