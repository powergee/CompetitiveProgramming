#include <iostream>
#include <algorithm>
#define MOD 998244353LL

using Long = long long;

int main() {
    int n;
    scanf("%d", &n);
    Long divCount[n+1], prevSum = 0, current;
    std::fill(divCount, divCount+n+1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            divCount[j]++;
        }
    }

    for (int i = 1; i <= n; ++i) {
        current = (prevSum + divCount[i]) % MOD;
        prevSum = (prevSum + current) % MOD;
    }

    printf("%lld", current);

    return 0;
}