#include <iostream>

typedef long long Long;
enum Selection { Upper, Lower };

int n, m;
Long height, upper[3000], lower[3000];
Long dp[3000][3000][2];

Long getDist(int u, int l) {
    Long width = std::abs(upper[u] - lower[l]);
    return height*height + width*width;
}

Long getMinDistSum(int uIdx, int lIdx, Selection next) {
    Long& result = dp[uIdx][lIdx][next];
    if (result != -1LL) {
        return result;
    }
    if (uIdx == 0 && lIdx == 0) {
        return result = getDist(0, 0) * (n+m-1);
    }

    result = __INT64_MAX__;
    if (0 < uIdx) {
        Long prev = getMinDistSum(uIdx-1, lIdx, Upper);
        Long coef = (next == Upper ? (n+m-1) : ((uIdx+lIdx+1)*(n+m-(uIdx+lIdx+1))));
        Long curr = getDist(uIdx, lIdx) * coef;
        result = std::min(result, prev+curr);
    }
    if (0 < lIdx) {
        Long prev = getMinDistSum(uIdx, lIdx-1, Lower);
        Long coef = (next == Lower ? (n+m-1) : ((uIdx+lIdx+1)*(n+m-(uIdx+lIdx+1))));
        Long curr = getDist(uIdx, lIdx) * coef;
        result = std::min(result, prev+curr);
    }

    return result;
}

int main() {
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Long), -1LL);
    scanf("%d %d %lld", &n, &m, &height);

    for (int i = 0; i < n; ++i) {
        scanf("%lld", upper+i);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%lld", lower+i);
    }
    
    printf("%lld", std::min(getMinDistSum(n-1, m-1, Upper), getMinDistSum(n-1, m-1, Lower)));

    return 0;
}