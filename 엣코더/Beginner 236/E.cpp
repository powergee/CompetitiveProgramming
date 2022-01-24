#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#define SCALE 1000

typedef long long Long;

Long getMaxSum(const std::vector<Long>& arr) {
    if (arr.size() == 1) {
        return arr[0];
    }

    int n = arr.size();
    std::vector<Long> dp(n, 0);
    dp[0] = arr[0];
    dp[1] = std::max(arr[0]+arr[1], arr[1]);

    for (int i = 2; i < n; ++i) {
        dp[i] = std::max(dp[i-2], dp[i-1]) + arr[i];
    }
    return std::max(dp[n-2], dp[n-1]);
}

void printMaxAvg(const std::vector<Long>& arr) {
    auto isPossible = [&](Long avg) -> bool {
        std::vector<Long> converted(arr.size());
        for (int i = 0; i < arr.size(); ++i) {
            converted[i] = arr[i] - avg;
        }
        return 0 <= getMaxSum(converted);
    };

    Long left = 0, right = *std::max_element(arr.begin(), arr.end());
    while (left+1 < right) {
        Long mid = (left+right)/2;
        if (isPossible(mid)) {
            left = mid;
        } else {
            right = mid-1;
        }
    }
    
    Long result = isPossible(right) ? right : left;
    if (result < SCALE) {
        printf("0.%03lld\n", result);
    } else {
        printf("%lld.%03lld\n", result/SCALE, result%SCALE);
    }
}

void printMaxMed(const std::vector<Long>& arr) {
    auto isPossible = [&](Long med) -> bool {
        std::vector<Long> converted(arr.size());
        for (int i = 0; i < arr.size(); ++i) {
            converted[i] = med <= arr[i] ? 1 : -1;
        }
        return 0 < getMaxSum(converted);
    };

    auto sorted = arr;
    std::sort(sorted.begin(), sorted.end());
    Long left = 0, right = int(arr.size())-1;
    while (left+1 < right) {
        Long mid = (left+right)/2;
        if (isPossible(sorted[mid])) {
            left = mid;
        } else {
            right = mid-1;
        }
    }

    Long result = isPossible(sorted[right]) ? sorted[right] : sorted[left];
    printf("%lld\n", result/SCALE);
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
        arr[i] *= SCALE;
    }

    printMaxAvg(arr);
    printMaxMed(arr);

    return 0;
}