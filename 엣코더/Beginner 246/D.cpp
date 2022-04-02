#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>

typedef long long Long;

int main() {
    Long n;
    scanf("%lld", &n);

    Long answer = INT64_MAX;
    for (Long a = 0; 0 <= a*a*a && a*a*a <= n; ++a) {
        Long left = 0, right = 1e6+1;
        while (left < right) {
            Long b = (left+right) / 2;
            Long x = a*a*a + a*a*b + a*b*b + b*b*b;
            if (n <= x) {
                right = b;
            } else {
                left = b+1;
            }
        }
        Long b = left;
        answer = std::min(answer, a*a*a + a*a*b + a*b*b + b*b*b);
    }

    printf("%lld", answer);

    return 0;
}