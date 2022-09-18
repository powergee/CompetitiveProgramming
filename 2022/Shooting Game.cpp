#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    if (k == 0) {
        std::cout << 0 << "\n";
        return 0;
    }
    
    std::vector<std::pair<int, int>> meteor;
    for (int i = 0; i < k; ++i) {
        int r, c;
        std::cin >> r >> c;
        meteor.emplace_back(r, c);
    }
    std::sort(meteor.begin(), meteor.end(), [&](auto p, auto q) {
        return p.second < q.second;
    });

    std::vector<int> columns(k);
    for (int i = 0; i < k; ++i) {
        columns[i] = meteor[i].second;
    }

    bool isCollapsed[n+1][1<<k];
    for (int elapsed = 0; elapsed <= n; ++elapsed) {
        for (int mask = 0; mask < (1<<k); ++mask) {
            for (int i = 0; i < k; ++i) {
                isCollapsed[elapsed][mask] = false;
                if ((mask&(1<<i)) && meteor[i].first+elapsed >= n) {
                    isCollapsed[elapsed][mask] = true;
                    break;
                }
            }
        }
    }

    // elapsed, airplane pos, meteor mask
    int dp[n+1][k][1<<k];
    for (int elapsed = n; elapsed >= 0; --elapsed) {
        for (int pos = 0; pos < k; ++pos) {
            for (int mask = 0; mask < (1<<k); ++mask) {
                int& result = dp[elapsed][pos][mask];

                if (mask == 0) {
                    result = elapsed;
                    continue;
                }
                if (isCollapsed[elapsed][mask]) {
                    result = INT32_MAX;
                    continue;
                }
                
                result = INT32_MAX;
                if (mask&(1<<pos)) {
                    int sub = dp[elapsed+1][pos][mask^(1<<pos)];
                    result = std::min(sub, result);
                }
                if (pos+1 < k && elapsed+columns[pos+1]-columns[pos] <= n) {
                    int sub = dp[elapsed+columns[pos+1]-columns[pos]][pos+1][mask];
                    result = std::min(sub, result);
                }
                if (pos-1 >= 0 && elapsed+columns[pos]-columns[pos-1] <= n) {
                    int sub = dp[elapsed+columns[pos]-columns[pos-1]][pos-1][mask];
                    result = std::min(sub, result);
                }
            }
        }
    }

    int currCol;
    std::cin >> currCol;
    int answer = INT32_MAX;
    int right = std::lower_bound(columns.begin(), columns.end(), currCol) - columns.begin();
    if (right < k) {
        int sub = dp[columns[right]-currCol][right][(1<<k)-1];
        answer = std::min(answer, sub);
    }
    int left = right-1;
    if (left >= 0) {
        int sub = dp[currCol-columns[left]][left][(1<<k)-1];
        answer = std::min(answer, sub);
    }

    std::cout << (answer == INT32_MAX ? -1 : answer) << "\n";

    return 0;
}