#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n, x;
        scanf("%lld %lld", &n, &x);

        std::vector<Long> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &arr[i]);
        }

        Long count = 0;
        std::multiset<Long> exist(arr.begin(), arr.end());
        std::sort(arr.begin(), arr.end());
        for (Long v : arr) {
            auto currIter = exist.find(v);
            if (currIter != exist.end()) {
                auto multIter = exist.find(v*x);
                if (multIter != exist.end()) {
                    exist.erase(multIter);
                } else {
                    ++count;
                }
                exist.erase(currIter);
            }
        }

        printf("%lld\n", count);
    }

    return 0;
}