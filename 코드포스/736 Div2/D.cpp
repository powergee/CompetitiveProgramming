#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

typedef long long Long;

Long arr[200000];
Long diff[200000];
std::unordered_map<Long, Long> dp[200000];
std::unordered_set<Long> used;

Long getMaxLength(int right, Long gcd) {
    if (dp[right].find(gcd) != dp[right].end()) {
        return dp[right][gcd];
    }
    used.insert(right);

    Long result;
    if (gcd == 1) {
        result = 0;
    } else if (right == 0) {
        result = 1;
    } else {
        result = getMaxLength(right-1, std::gcd(gcd, diff[right-1])) + 1;
    }

    dp[right][gcd] = result;
    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%lld", &arr[i]);
        }

        if (n == 1) {
            printf("1\n");
            continue;
        }

        for (int i = 0; i < n-1; ++i) {
            diff[i] = std::abs(arr[i] - arr[i+1]);
        }

        Long maxLength = 0;
        for (int r = 0; r < n-1; ++r) {
            maxLength = std::max(maxLength, getMaxLength(r, diff[r]));
        }
        printf("%lld\n", maxLength+1);

        for (Long right : used) {
            dp[right].clear();
        }
        used.clear();
    }

    return 0;
}