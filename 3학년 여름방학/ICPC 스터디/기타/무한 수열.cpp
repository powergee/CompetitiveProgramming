#include <iostream>
#include <unordered_map>

using Long = long long;
std::unordered_map<Long, Long> dp;
Long n, p, q;

Long getAnswer(Long index) {
    if (dp.find(index) != dp.end()) {
        return dp[index];
    }

    return dp[index] = getAnswer(index/p) + getAnswer(index/q);
}

int main() {
    scanf("%lld %lld %lld", &n, &p, &q);
    dp[0] = 1;
    printf("%lld", getAnswer(n));

    return 0;
}