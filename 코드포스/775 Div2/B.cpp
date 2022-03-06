#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<Long> arr(n);
        bool allZero = true;
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &arr[i]);
            if (arr[i]) {
                allZero = false;
            }
        }

        if (allZero) {
            printf("0\n");
        } else {
            std::sort(arr.begin(), arr.end());
            Long biggest = arr.back();
            Long spare = std::accumulate(arr.begin(), arr.end()-1, 0LL);
            
            if (biggest > spare+1) {
                printf("%lld\n", biggest-spare);
            } else {
                printf("1\n");
            }
        }
    }

    return 0;
}