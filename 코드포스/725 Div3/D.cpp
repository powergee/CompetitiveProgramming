#include <iostream>
#include <numeric>

int countPrimes(int val) {
    int count = 0;
    int origin = val;
    
    for (int d = 2; d*d <= origin; ++d) {
        while (val % d == 0) {
            val /= d;
            count++;
        }
    }
    if (val > 1) {
        count++;
    }

    return count;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);
        int gcd = std::gcd(a, b);

        int aSpare = countPrimes(a / gcd);
        int bSpare = countPrimes(b / gcd);
        int gSpare = countPrimes(gcd);

        bool yes;

        if (k == 1) {
            if ((aSpare > 0) ^ (bSpare > 0)) {
                yes = true;
            } else {
                yes = false;
            }
        } else if (k <= aSpare + bSpare) {
            yes = true;
        } else if ((k-aSpare-bSpare) <= 2*gSpare) {
            yes = true;
        } else {
            yes = false;
        }

        if (yes) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}