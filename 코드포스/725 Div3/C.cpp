#include <iostream>
#include <algorithm>

int arr[200000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, l, r;
        scanf("%d %d %d", &n, &l, &r);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }
        std::sort(arr, arr+n);

        long long answer = 0;
        for (int i = 0; i < n-1; ++i) {
            auto lp = std::lower_bound(arr+i+1, arr+n, l-arr[i]);
            auto rp = std::upper_bound(arr+i+1, arr+n, r-arr[i]);
            if (lp <= rp) {
                answer += rp - lp;
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}