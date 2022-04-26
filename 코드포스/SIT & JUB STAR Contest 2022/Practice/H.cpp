#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000002

typedef long long Long;

int main() {
    std::vector<int> sellCount(MAX, 0), buyCount(MAX, 0);
    std::vector<Long> sellSum(MAX, 0), buySum(MAX, 0);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        sellCount[v]++;
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int v;
        scanf("%d", &v);
        buyCount[v]++;
    }

    for (int i = 1; i <= MAX-2; ++i) {
        sellSum[i] = sellSum[i-1] + sellCount[i];
    }
    for (int i = MAX-2; i >= 1; --i) {
        buySum[i] = buyCount[i] + buySum[i+1];
    }

    Long answer = 0;
    for (Long x = 1; x <= MAX-2; ++x) {
        Long profit = std::min(sellSum[x], buySum[x]) * x;
        answer = std::max(answer, profit);
    }

    printf("%lld", answer);

    return 0;
}