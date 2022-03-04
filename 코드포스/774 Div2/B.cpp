#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<Long> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &arr[i]);
        }

        std::sort(arr.begin(), arr.end());
        std::vector<Long> preSum(n);
        std::partial_sum(arr.begin(), arr.end(), preSum.begin());

        bool possible = false;
        for (int redStart = n-1; redStart >= 2; --redStart) {
            int redCount = n-redStart;
            int blueMaxCount = n-redCount;
            if (blueMaxCount <= redCount) {
                break;
            }

            Long redSum = preSum[n-1] - preSum[redStart-1];
            Long blueSum = preSum[redCount];

            if (redSum > blueSum) {
                possible = true;
                break;
            }
        }

        if (possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}