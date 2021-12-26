#include <iostream>
#include <vector>
#include <map>

typedef long long Long;

int main() {
    Long n, k;
    scanf("%lld %lld", &n, &k);

    std::vector<Long> arr(n+1, 0);
    std::vector<Long> sum(n+1, 0);
    std::map<Long, int> count;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &arr[i]);
        sum[i] = sum[i-1] + arr[i];
        count[sum[i]] += 1;
    }

    Long total = 0;
    for (int i = 1; i <= n; ++i) {
        Long target = k+sum[i-1];
        if (count.find(target) != count.end()) {
            total += count[target];
        }
        count[sum[i]] -= 1;
    }

    printf("%lld", total);

    return 0;
}