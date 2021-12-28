#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &nums[i]);
        }

        int maxK = 0;
        for (int base : nums) {
            int zeros = 0;
            std::vector<int> filtered;
            for (int i = 0; i < n; ++i) {
                if (base <= nums[i]) {
                    filtered.push_back(nums[i]-base);
                    zeros += (nums[i]-base == 0 ? 1 : 0);
                }
            }

            if (filtered.size() < n/2) {
                continue;
            } else if (zeros >= n/2) {
                maxK = -1;
                break;
            }

            int bound = *std::max_element(filtered.begin(), filtered.end());
            for (int k = bound; k >= 1; --k) {
                int satisfied = 0;
                for (int f : filtered) {
                    if (f % k == 0) {
                        ++satisfied;
                    }
                }
                if (satisfied >= n/2) {
                    maxK = std::max(maxK, k);
                    break;
                }
            }
        }

        printf("%d\n", maxK);
    }

    return 0;
}