#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

int arr[100001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        long long k;
        scanf("%d %lld", &n, &k);
        std::vector<std::vector<int>> indexes(n+1);

        for (int i = 1; i <= n; ++i) {
            scanf("%d", arr+i);
            indexes[arr[i]].push_back(i);
        }

        Long answer = -__INT64_MAX__;
        for (Long diff = 1; diff <= k; ++diff) {
            for (Long i = 1; i+diff <= n; ++i) {
                Long j = i+diff;
                answer = std::max(answer, i*j - k*(arr[i]|arr[j]));
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}