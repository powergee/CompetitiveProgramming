#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        std::sort(arr.begin(), arr.end(), std::greater<int>());
        for (int i = 1; i < n; ++i) {
            arr[i] += arr[i-1];
        }

        while (m--) {
            int q;
            scanf("%d", &q);
            auto found = std::lower_bound(arr.begin(), arr.end(), q);
            if (found == arr.end()) {
                printf("-1\n");
            } else {
                printf("%d\n", int(found-arr.begin()+1));
            }
        }
    }

    return 0;
}