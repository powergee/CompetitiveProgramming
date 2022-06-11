#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        int possible = (n-1) + n*(m-1);
        printf(possible == k ? "YES\n" : "NO\n");
    }

    return 0;
}