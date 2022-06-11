#include <iostream>

typedef long long Long;

Long a[5001], b[5001];
Long prodSum[5001];
Long dp[5001][5001];

Long getProdSum(int left, int right) {
    if (right < left) {
        return 0;
    }
    return prodSum[right] - prodSum[left-1];
}

Long getRevProdSum(int left, int right) {
    if (dp[left][right] != -1) {
        return dp[left][right];
    }

    if (right < left) {
        dp[left][right] = 0;
    } else if (left == right) {
        dp[left][right] = a[left]*b[left];
    } else {
        dp[left][right] = a[left]*b[right] + a[right]*b[left] + getRevProdSum(left+1, right-1);
    }

    return dp[left][right];
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a+i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", b+i);
        std::fill(dp[i], dp[i]+n+1, -1LL);
    }

    for (int i = 1; i <= n; ++i) {
        prodSum[i] = prodSum[i-1] + (a[i]*b[i]);
    }

    Long answer = getProdSum(1, n);
    for (int i = 1; i <= n-1; ++i) {
        for (int j = i+1; j <= n; ++j) {
            Long curr = getProdSum(1, i-1) + getRevProdSum(i, j) + getProdSum(j+1, n);
            answer = std::max(curr, answer);
        }
    }

    printf("%lld", answer);

    return 0;
}