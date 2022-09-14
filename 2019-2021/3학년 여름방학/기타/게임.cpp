#include <iostream>

typedef long long Long;

Long x, y, initZ;

bool zIsChanged(int winCount) {
    Long newX = x + winCount;
    Long newY = y + winCount;
    return initZ != ((100*newY) / newX);
}

int main() {
    scanf("%lld %lld", &x, &y);
    initZ = (100*y) / x;

    if (initZ >= 99) {
        printf("-1");
    } else {
        Long left = 1;
        Long right = 1000000000;
        while (left < right) {
            Long mid = (left+right) / 2;
            if (zIsChanged(mid)) {
                right = mid;
            } else {
                left = mid+1;
            }
        }
        printf("%lld", left);
    }

    return 0;
}