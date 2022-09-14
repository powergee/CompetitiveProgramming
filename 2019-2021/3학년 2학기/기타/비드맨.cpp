#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

typedef long long Long;

Long greedyMatch(std::vector<Long>& arr) {
    Long sum = std::accumulate(arr.begin(), arr.end(), 0LL);
    Long max = *std::max_element(arr.begin(), arr.end());
    Long spare = sum - max;

    if (max < spare) {
        return sum % 2 == 0 ? 0LL : 1LL;
    } else {
        return max - spare;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    std::vector<Long> arr(n);

    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }
    printf("%lld", greedyMatch(arr));

    return 0;
}
