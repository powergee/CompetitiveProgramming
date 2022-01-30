#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        char str[n+1];
        scanf("%s", str);

        if (n == 1) {
            printf("YES\n");
        } else if (n == 2) {
            printf(str[0] != str[1] ? "YES\n" : "NO\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}