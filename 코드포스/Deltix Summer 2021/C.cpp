#include <iostream>

typedef long long Long;

Long count[1001];
std::pair<Long, Long> dp[1001][1001];

std::pair<Long, Long> countUnpaired(int left, int right) {
    if (right <= left) {
        return { 0, 0 };
    }

    auto& result = dp[left][right];
    if (result.first != -1) {
        return result;
    }

    if ((left % 2) == (right % 2)) {
        exit(1);
    }
    
    auto inner = countUnpaired(left+1, right-1);
    if (left % 2 == 1) {
        Long leftVec = inner.first - count[left];
        Long rightVec = inner.second - count[right];
        if (0 <= leftVec && 0 <= rightVec) {
            result = { leftVec, rightVec };
        } else if (0 <= leftVec && rightVec < 0) {
            result = { leftVec-rightVec, 0 };
        } else if (leftVec < 0 && 0 <= rightVec) {
            result = { 0, -leftVec+rightVec };
        } else if (std::abs(leftVec) <= std::abs(rightVec)) {
            result = { leftVec-rightVec, 0 };
        } else {
            result = { 0, rightVec-leftVec };
        }
    } else {
        result = { inner.first + count[left], inner.second + count[right] };
    }
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", count+i);
        std::fill(dp[i]+i, dp[i]+n+1, std::make_pair(-1LL, -1LL));
    }

    Long answer = 0;
    for (int i = 1; i <= n; i += 2) {
        for (int j = i+1; j <= n; j += 2) {
            auto inner = countUnpaired(i+1, j-1);
            Long minLeft = std::max(1LL, inner.first);
            Long minRight = std::max(1LL, inner.second);
 
            if (minLeft <= count[i] && minRight <= count[j]) {
                answer += std::min(count[i]-minLeft+1, count[j]-minRight+1);
            }
        }
    }


    printf("%lld", answer);

    return 0;
}