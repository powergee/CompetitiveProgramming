#include <iostream>

typedef long long Long;

Long dp[21][21][21];

Long w(int a, int b, int c) {
    if (a <= 0 or b <= 0 or c <= 0) {
        return 1;
    } else if (a > 20 or b > 20 or c > 20) {
        return w(20, 20, 20);
    } else if (dp[a][b][c]) {
        return dp[a][b][c];
    } else if (a < b and b < c) {
        return dp[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
    } else {
        return dp[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
    }
}

int main() {
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c), (a != -1 || b != -1 || c != -1)) {
        printf("w(%d, %d, %d) = %lld\n", a, b, c, w(a, b, c));
    }
    return 0;
}