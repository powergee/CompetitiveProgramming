#include <iostream>
#include <algorithm>

int n;
int arr[1000];
int dp[1000];

int getMaxDiff(int start) {
    if (start == n) {
        return 0;
    }

    int& result = dp[start];
    if (result != -1) {
        return result;
    }

    int min = __INT32_MAX__;
    int max = -__INT32_MAX__;

    for (int i = start; i < n; ++i) {
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
        result = std::max(result, max-min + getMaxDiff(i+1));
    }

    return result;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        dp[i] = -1;
    }

    printf("%d", getMaxDiff(0));

    return 0;
}