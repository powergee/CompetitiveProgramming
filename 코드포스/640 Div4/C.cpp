#include <iostream>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n, k;
        scanf("%lld %lld", &n, &k);

        Long left = 0, right = 2e9;
        while (left+1 < right) {
            Long mid = (left+right) / 2;
            Long count = (n-1)*mid;
            if (count < k) {
                left = mid;
            } else {
                right = mid-1;
            }
        }
        if ((n-1)*right < k) {
            left = right;
        }

        printf("%lld\n", n*left + k-((n-1)*left));
    }
    
    return 0;
}