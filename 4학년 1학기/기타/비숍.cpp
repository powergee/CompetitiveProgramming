#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> map(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    std::vector<std::vector<int>> dp((1<<(2*n)), std::vector<int>(2*n-1, -1));

    auto isOne = [](int mask, int index) -> bool {
        return mask & (1<<index);
    };
    
    std::function<int(int, int)> countBishops = [&](int slashMask, int bSlashStart) -> int {
        if (2*n-1 <= bSlashStart) {
            return 0;
        }

        int& result = dp[slashMask][bSlashStart];
        if (result != -1) {
            return result;
        }

        result = countBishops(slashMask, bSlashStart+1);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r-c == bSlashStart-(n-1) && map[r][c] && !isOne(slashMask, r+c)) {
                    result = std::max(1+countBishops(slashMask|(1<<(r+c)), bSlashStart+1), result);
                }
            }
        }

        return result;
    };

    printf("%d", countBishops(0, 0));

    return 0;
}