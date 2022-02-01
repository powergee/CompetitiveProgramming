#include <iostream>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long hc, dc, hm, dm, k, w, a;
        scanf("%lld %lld\n%lld %lld", &hc, &dc, &hm, &dm);
        scanf("%lld %lld %lld", &k, &w, &a);

        bool yes = false;
        for (Long kh = 0; kh <= k; ++kh) {
            Long kd = k-kh;
            Long cLife = (hc + a*kh) / dm + ((hc + a*kh) % dm ? 1 : 0);
            Long mLife = hm / (dc + w*kd) + (hm % (dc + w*kd) ? 1 : 0);
            if (cLife >= mLife) {
                yes = true;
            }
        }
        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}