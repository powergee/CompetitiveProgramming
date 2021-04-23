#include <iostream>

typedef long long Long;

Long getNear(Long val) {
    Long result = 2050;
    while (result*10 <= val) {
        result *= 10;
    }

    if (result > val) {
        return -1;
    }
    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n;
        scanf("%lld", &n);

        int answer = 0;
        while (n > 0) {
            Long sub = getNear(n);
            if (sub == -1) {
                answer = -1;
                break;
            }
            n -= sub;
            ++answer;
        }

        printf("%d\n", answer);
    }

    return 0;
}