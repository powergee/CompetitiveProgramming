#include <iostream>
#include <algorithm>
#include <vector>
#define MOD 1000000007LL

typedef long long Long;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<Long> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &b[i]);
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    Long sum = 0;
    for (int i = 0; i < n-1; ++i) {
        sum += a[i] * b[i];
        sum %= MOD;
    }

    Long smaller = std::min(a.back(), b.back());
    Long bigger = std::max(a.back(), b.back());
    if (k <= bigger-smaller) {
        sum += (bigger * (smaller+k)) % MOD;
        sum %= MOD;
    } else {
        k -= bigger-smaller;
        smaller = bigger;
        bigger += k/2;
        smaller += k-k/2;
        sum += (bigger * smaller) % MOD;
        sum %= MOD;
    }

    printf("%lld\n", sum);

    return 0;
}