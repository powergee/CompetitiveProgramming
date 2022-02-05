#include <iostream>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long a, s;
        scanf("%lld %lld", &a, &s);

        Long o = s-a;
        if (o >= 0 && (o & a) == a) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}