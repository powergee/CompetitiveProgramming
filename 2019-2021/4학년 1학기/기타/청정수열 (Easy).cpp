#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    long long sum = 1;
    for (int i = 1; i <= n; ++i) {
        sum *= i;
    }
    printf("%lld", sum);

    return 0;
}