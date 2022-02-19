#include <iostream>
#include <vector>

int main() {
    const int last = 200;
    std::vector<bool> isPrime(last + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int div = 2; div*div <= last; ++div) {
        if (isPrime[div]) {
            for (int i = div*div; i <= last; i += div) {
                isPrime[i] = false;
            }
        }
    }

    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    for (int ta = a; ta <= b; ++ta) {
        bool takahashiCanWin = true;
        for (int ao = c; ao <= d; ++ao) {
            if (isPrime[ta+ao]) {
                takahashiCanWin = false;
                break;
            }
        }
        if (takahashiCanWin) {
            printf("Takahashi");
            return 0;
        }
    }

    printf("Aoki");
    return 0;
}