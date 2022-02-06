#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        char str[n+1];
        scanf("%s", str);

        bool isPalin = true;
        for (int i = 0; i < n/2; ++i) {
            if (str[i] != str[n-1-i]) {
                isPalin = false;
            }
        }

        if (isPalin) {
            printf("1\n");
        } else if (k == 0) {
            printf("1\n");
        } else {
            printf("2\n");
        }
    }

    return 0;
}