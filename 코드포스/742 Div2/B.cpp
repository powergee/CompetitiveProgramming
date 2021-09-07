#include <iostream>

typedef long long Long;

Long xorSum[300001];

int main() {
    xorSum[0] = 0;
    for (int i = 1; i < sizeof(xorSum)/sizeof(Long); ++i) {
        xorSum[i] = xorSum[i-1] ^ i;
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        Long a, b;
        scanf("%lld %lld", &a, &b);

        Long result = a;

        if (xorSum[a-1] != b) {
            int k = xorSum[a-1] ^ b;
            if (k == a) {
                result += 2;
            } else {
                result++;
            }
        }

        printf("%lld\n", result);
    }

    return 0;
}