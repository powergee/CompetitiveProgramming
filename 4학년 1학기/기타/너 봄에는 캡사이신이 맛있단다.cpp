#include <iostream>
#include <vector>
#include <algorithm>
#define MOD 1000000007

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::sort(arr.begin(), arr.end());

    Long answer = 0;
    Long currSum = 0, mask = 0;
    for (int i = 0; i+1 < n; ++i) {
        mask <<= 1;
        mask += 1;
        mask %= MOD;
        currSum <<= 1;
        currSum += (arr[i+1]-arr[i]) * mask;
        currSum %= MOD;
        answer += currSum;
        answer %= MOD;
    }

    std::cout << answer;

    return 0;
}