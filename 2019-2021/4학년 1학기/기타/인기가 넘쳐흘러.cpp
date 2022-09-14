#include <iostream>
#include <vector>

int dp[301][301][301];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k, t;
    std::cin >> n >> m >> k >> t;

    std::vector<int> fixed(n+2, 0);
    for (int i = 0; i < m; ++i) {
        int s, e;
        std::cin >> s >> e;
        fixed[s]++;
        fixed[e]--;
    }
    for (int i = 1; i < n+2; ++i) {
        fixed[i] += fixed[i-1];
    }

    for (int activated = 0; activated <= k; ++activated) {
        for (int remaining = 0; remaining <= k; ++remaining) {
            dp[n][activated][remaining] = (fixed[n]+activated >= t ? 1 : 0);
        }
    }

    for (int time = n-1; time >= 1; --time) {
        for (int activated = k; activated >= 0; --activated) {
            for (int remaining = 0; remaining <= k; ++remaining) {
                int& result = dp[time][activated][remaining];
                int base = (fixed[time]+activated >= t ? 1 : 0);
                if (fixed[time] >= t) {
                    result = base + dp[time+1][0][remaining];
                } else {
                    result = base + dp[time+1][activated][remaining];
                    if (activated+1 <= k && remaining-1 >= 0) {
                        result = std::max(result, dp[time][activated+1][remaining-1]);
                    }
                }
            }
        }
    }

    std::cout << dp[1][0][k];

    return 0;
}