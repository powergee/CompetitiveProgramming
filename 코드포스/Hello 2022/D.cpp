#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        n *= 2;
        
        std::vector<std::vector<int>> map(n, std::vector<int>(n, 0));
        Long basis = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &map[i][j]);
                if (n/2 <= i && n/2 <= j) {
                    basis += map[i][j];
                    map[i][j] = 0;
                }
            }
        }

        int minDist = INT32_MAX;
        minDist = std::min(minDist, map[0][n/2]);
        minDist = std::min(minDist, map[0][n-1]);
        minDist = std::min(minDist, map[n/2-1][n/2]);
        minDist = std::min(minDist, map[n/2-1][n-1]);
        minDist = std::min(minDist, map[n/2][0]);
        minDist = std::min(minDist, map[n/2][n/2-1]);
        minDist = std::min(minDist, map[n-1][0]);
        minDist = std::min(minDist, map[n-1][n/2-1]);

        printf("%lld\n", minDist + basis);
    }

    return 0;
}