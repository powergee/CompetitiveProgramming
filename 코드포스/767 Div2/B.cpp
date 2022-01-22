#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);

        bool possible = false;
        int length = r-l+1;
        int oddCount = length / 2 + (length % 2 == 1 && l % 2 == 1 ? 1 : 0);

        if ((length == 1 && l != 1) || oddCount <= k) {
            possible = true;
        }

        printf(possible ? "YES\n" : "NO\n");
    }

    return 0;
}