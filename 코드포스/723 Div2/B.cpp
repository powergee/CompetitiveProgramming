#include <iostream>
#include <cstring>

char str[11];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int mod = n % 11;
        if (mod <= n / 111) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}