#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>

using Real = double;
using Complex = std::complex<Real>;
const Real PI = std::acos(-1.L);

inline unsigned reverseBits(const unsigned n, const unsigned k) {
    unsigned r, i;
    for (r = 0, i = 0; i < k; ++i)
        r |= ((n >> i) & 1) << (k - i - 1);
    return r;
}

void FFT(std::vector<Complex> &a, bool isReversed = false) {
    const unsigned n = a.size(), k = __builtin_ctz(n);
    unsigned s, i, j;
    for (i = 0; i < n; i++) {
        j = reverseBits(i, k);
        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }
    for (s = 2; s <= n; s *= 2) {
        std::vector<Complex> w(s / 2);
        for (i = 0; i < s / 2; i++) {
            Real t = 2 * PI * i / s * (isReversed ? -1 : 1);
            w[i] = Complex(std::cos(t), std::sin(t));
        }
        for (i = 0; i < n; i += s) {
            for (j = 0; j < s / 2; j++) {
                Complex tmp = a[i + j + s / 2] * w[j];
                a[i + j + s / 2] = a[i + j] - tmp;
                a[i + j] += tmp;
            }
        }
    }
    if (isReversed) {
        for (i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

std::vector<Complex> getSquare(std::vector<Complex> &a) {
	auto aCopy = a;
	unsigned n = 1;
	while (n <= a.size()) {
		n *= 2;
    }
	n *= 2;

	aCopy.resize(n, 0);
    FFT(aCopy);

	std::vector<Complex> result(n);
    for (unsigned i = 0; i < n; i++) {
        result[i] = aCopy[i] * aCopy[i];
    }
    FFT(result, true);

	return result;
}

bool isPrime[1000001];

int main() {
    std::fill(isPrime, isPrime+1000001, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i*i < 1000001; ++i) {
        if (isPrime[i]) {
            for (int j = i*i; j < 1000001; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::vector<Complex> primes(500000, Complex(0, 0));
    for (int i = 3; i < 1000001; ++i) {
        if (isPrime[i]) {
            primes[(i-1)/2] = Complex(1, 0);
        }
    }
    
    auto conv = getSquare(primes);

    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        if (n == 4) {
            printf("1\n");
        } else {
            printf("%lld\n", (long long)std::round(std::round(conv[n/2-1].real())/2));
        }
    }

    return 0;
}