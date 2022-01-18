#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        bool yes = false;
        int at = b-(c-b);
        if (at > 0 && at % a == 0) {
            yes = true;
        }
        int bt = a+(c-a)/2;
        if ((c-a)%2 == 0 && bt > 0 && bt % b == 0) {
            yes = true;
        }
        int ct = b+(b-a);
        if (ct > 0 && ct % c == 0) {
            yes = true;
        }

        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}