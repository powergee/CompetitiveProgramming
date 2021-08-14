#include <iostream>
#include <algorithm>
#include <map>
#define MOD 1000000007

typedef long long Long;

int arr[500000], max[500000];
Long dp[500000];
std::vector<std::pair<int, int>> counts;

Long countCases(int start) {
    if (start == counts.size()) {
        return 1;
    }
    
    if (dp[start] != -1) {
        return dp[start];
    }

    Long result = (countCases(start+1) * (counts[start].second+1)) % MOD;
    return dp[start] = result;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }

    max[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        max[i] = std::max(max[i-1], arr[i]);
    }
    
    std::map<int, int> maxCount;
    for (int i = 0; i < n; ++i) {
        maxCount[max[i]]++;
    }
    counts = std::vector<std::pair<int, int>>(maxCount.begin(), maxCount.end());
    counts.pop_back();

    if (counts.empty()) {
        printf("1\n");
    } else {
        std::fill(dp, dp+counts.size(), -1LL);
        Long result = countCases(0);
        printf("%lld", result);
    }

    return 0;
}