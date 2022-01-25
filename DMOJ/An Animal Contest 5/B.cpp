#include <iostream>
#include <vector>
#include <numeric>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> mult(n+1);
    for (int i = 2; i <= n; ++i) {
        printf("? 1 %d\n", i);
        fflush(stdout);
        scanf("%lld", &mult[i]);
    }

    std::vector<Long> answer(n+1);
    answer[1] = mult[2];
    for (int i = 3; i <= n; ++i) {
        answer[1] = std::gcd(mult[i], answer[1]);
    }

    for (int i = 2; i <= n; ++i) {
        answer[i] = mult[i] / answer[1];
    }

    printf("!");
    for (int i = 1; i <= n; ++i) {
        printf(" %lld", answer[i]);
    }
    printf("\n");

    return 0;
}