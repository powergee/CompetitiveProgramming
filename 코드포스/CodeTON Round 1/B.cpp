#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<Long> arr(n);
        std::set<Long> arrSet;
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &arr[i]);
            arrSet.insert(arr[i]);
        }
        
        bool possible = false;
        for (int i = 0; i < n; ++i) {
            if (arrSet.count(arr[i]-k)) {
                possible = true;
            }
        }
        printf(possible ? "YES\n" : "NO\n");
    }

    return 0;
}