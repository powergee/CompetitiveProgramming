#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    Long max = 0;
    std::vector<Long> queries(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &queries[i]);
        max = std::max(max, queries[i]);
    }

    std::vector<std::vector<Long>> factors(max+1);
    std::vector<bool> isPrime(max+1, true), hasQuery(max+1, false);

    for (int i = 0; i < n; ++i) {
        hasQuery[queries[i]] = true;
    }

    for (Long i = 2; i*i <= max; ++i) {
        if (isPrime[i]) {
            for (Long j = i*2; j <= max; j += i) {
                isPrime[j] = false;
                if (hasQuery[j]) {
                    Long copy = j;
                    while (copy % i == 0) {
                        factors[j].push_back(i);
                        copy /= i;
                    }
                }
            }
        }
    }

    for (Long q : queries) {
        for (Long f : factors[q]) {
            printf("%lld ", f);
            q /= f;
        }
        if (q > 1) {
            printf("%lld ", q);
        }
        printf("\n");
    }

    return 0;
}