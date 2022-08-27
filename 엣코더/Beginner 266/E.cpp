#include <iostream>

int main() {
    int n;
    scanf("%d", &n);
    
    long double expected[n+1];
    expected[1] = 3.5;
    for (int i = 2; i <= n; ++i) {
        long double sum = 0;
        for (int d = 1; d <= 6; ++d) {
            if (expected[i-1] > d) {
                sum += expected[i-1];
            } else {
                sum += d;
            }
        }
        expected[i] = sum / 6;
    }

    printf("%.16Lf", expected[n]);
    
    return 0;
}