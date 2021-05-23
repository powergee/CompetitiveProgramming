#include <iostream>
#define MOD 1000000000

int fibo[1000001];

int main() {
    int n;
    scanf("%d", &n);

    fibo[0] = 0;
    fibo[1] = 1;
    for (int i = 2; i <= std::abs(n); ++i) {
        fibo[i] = (fibo[i-1] + fibo[i-2]) % MOD;
    }
    
    if (n > 0) {
        printf("1\n");
        printf("%d", fibo[n]);
    } else if (n < 0) {
        if (std::abs(n) % 2) {
            printf("1\n");
        } else {
            printf("-1\n");
        }
        printf("%d", fibo[-n]);
    } else {
        printf("0\n0");
    }

    return 0;
}