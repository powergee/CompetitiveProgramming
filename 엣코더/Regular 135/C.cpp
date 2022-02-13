#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> count(30, 0), arr(n);
    Long naiveSum = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
        naiveSum += arr[i];
        for (int j = 0; j < 30; ++j) {
            if (arr[i] & (1<<j)) {
                count[j]++;
            }
        }
    }

    Long maxBenefit = 0;
    for (int i = 0; i < n; ++i) {
        Long benefit = 0;
        for (int j = 0; j < 30; ++j) {
            if (arr[i] & (1<<j)) {
                benefit -= (count[j] * (1<<j));
                benefit += ((n-count[j]) * (1<<j));
            }
        }
        if (maxBenefit < benefit) {
            maxBenefit = benefit;
        }
    }

    printf("%lld", naiveSum + maxBenefit);

    return 0;
}