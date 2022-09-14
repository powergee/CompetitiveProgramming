#include <iostream>
#include <algorithm>

int main() {
    bool isPrime[10001];
    std::fill(isPrime, isPrime+10001, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= 10000; ++i) {
        if (isPrime[i]) {
            for (int j = i*i; j <= 10000; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int m, n;
    scanf("%d%d", &m, &n);

    int min = -1;
    int sum = 0;
    for (int i = n; i >= m; --i) {
        if (isPrime[i]) {
            min = i;
            sum += i;
        }
    }

    if (min == -1) {
        printf("-1");
    } else {
        printf("%d\n%d", sum, min);
    }

    return 0;
}