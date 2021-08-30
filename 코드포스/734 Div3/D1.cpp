#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int r, c, k;
        scanf("%d %d %d", &r, &c, &k);
        
        if (r % 2 == 0) {
            if (k % 2 == 1) {
                printf("NO\n");
            } else {
                int capacity = (c/2) * r;
                printf(capacity >= k ? "YES\n" : "NO\n");
            }
        } else {
            k = (r*c/2) - k;
            if (k % 2 == 1) {
                printf("NO\n");
            } else {
                int capacity = (r/2) * c;
                printf(capacity >= k ? "YES\n" : "NO\n");
            }
        }
    }

    return 0;
}