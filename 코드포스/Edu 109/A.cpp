#include <iostream>

int getGCD(int u, int v) {
    int t;

    while (v) {
        t = u % v;
        u = v;
        v = t;
    }

    return u;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int d = 100-n;
        
        if (n == 0 || d == 0) {
            printf("1\n");
        } else {
            int g = getGCD(n, d);
            n /= g;
            d /= g;
            printf("%d\n", n+d);
        }
    }
}