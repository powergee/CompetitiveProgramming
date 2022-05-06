#include <iostream>
#include <vector>

typedef long long Long;

Long countTriangles(Long lines) {
    return lines*lines*2/3;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n;
        scanf("%lld", &n);

        // max ans is 38730.
        Long left = 2, right = 38731;
        while (left < right) {
            Long mid = (left+right)/2;
            if (n <= countTriangles(mid)) {
                right = mid;
            } else {
                left = mid+1;
            }
        }
        printf("%lld\n", left);
    }

    return 0;
}