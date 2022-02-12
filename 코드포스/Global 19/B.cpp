#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        std::for_each(arr.begin(), arr.end(), [](int& v) { scanf("%d", &v); });
        std::vector<std::vector<int>> mex(n, std::vector<int>(n));

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                std::set<int> inSet;
                for (int k = i; k <= j; ++k) {
                    inSet.insert(arr[k]);
                }
                for (int v = 0; ; ++v) {
                    if (inSet.find(v) == inSet.end()) {
                        mex[i][j] = v;
                        break;
                    }
                }
            }
        }

        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1 + mex[i][i];
            for (int j = i+1; j < n; ++j) {
                dp[i][j] = 1 + mex[i][j];
                for (int k = i; k < j; ++k) {
                    dp[i][j] = std::max(dp[i][j], dp[i][k] + 1 + mex[k+1][j]);
                }
            }
        }

        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                sum += dp[i][j];
            }
        }
        printf("%lld\n", sum);
    }

    return 0;
}