#include <iostream>

typedef long long Long;

int main() {
    Long n;
    scanf("%lld", &n);

    Long left = 1, right = INT32_MAX;
    while (left+1 < right) {
        Long mid = (left+right) / 2;
        if (mid*(mid+1)/2 <= n) {
            left = mid;
        } else {
            right = mid-1;
        }
    }

    Long answer = 0;
    if (right*(right+1)/2 <= n) {
        answer = right;
    } else {
        answer = left;
    }

    printf("%lld", answer);

    return 0;
}