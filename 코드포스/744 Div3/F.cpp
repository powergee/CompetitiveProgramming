#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, d;
        scanf("%d %d", &n, &d);
        std::vector<int> arr(n);
        std::vector<int> dp(n, -1);
        std::vector<bool> inStack(n, false);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        std::function<int(int)> getSegLength;
        getSegLength = [&](int start) -> int {
            if (arr[start] == 0) {
                return 0;
            }
            if (inStack[start]) {
                return INT32_MAX;
            }
            if (dp[start] != -1) {
                return dp[start];
            }

            inStack[start] = true;
            int next = getSegLength((start+d) % n);
            if (next == INT32_MAX) {
                dp[start] = INT32_MAX;
            } else {
                dp[start] = next + 1;
            }
            inStack[start] = false;

            return dp[start];
        };

        int maxLength = 0;
        for (int i = 0; i < n; ++i) {
            int length = getSegLength(i);
            if (length == INT32_MAX) {
                maxLength = -1;
                break;
            } else {
                maxLength = std::max(maxLength, length);
            }
        }

        printf("%d\n", maxLength);
    }

    return 0;
}