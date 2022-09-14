#include <iostream>
#include <unordered_map>
#define MOD 1000

int a, b, d, n;
int history[1000001];
int sumDP[1000001];

int getSum(int right) {
    if (right < 0) {
        return 0;
    }
    if (sumDP[right] != -1) {
        return sumDP[right];
    }

    return sumDP[right] = (history[right] + getSum(right-1)) % MOD;
}

int getSum(int left, int right) {
    int result = getSum(right) - getSum(left-1);
    if (result < 0) {
        return (result+MOD) % MOD;
    }
    return result;
}

int main() {
    scanf("%d %d %d %d", &a, &b, &d, &n);

    std::fill(history, history+n+1, -1);
    std::fill(sumDP, sumDP+n+1, -1);
    history[0] = 1;

    for (int t = 1; t <= n; ++t) {
        int adult = getSum(t-b+1, t-a);
        history[t] = adult;
    }

    printf("%d", getSum(n-d+1, n));

    return 0;
}