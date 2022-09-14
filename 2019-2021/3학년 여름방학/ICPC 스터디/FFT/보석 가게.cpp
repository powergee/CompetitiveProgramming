#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>

using Long = long long;
using Real = double;
using Complex = std::complex<Real>;
const Real PI = std::acos(-1.L);

inline unsigned reverseBits(const unsigned n, const unsigned k) {
    unsigned r, i;
    for (r = 0, i = 0; i < k; ++i) {
        r |= ((n >> i) & 1) << (k - i - 1);
    }
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

void applyConvolution(std::vector<Complex> &a, std::vector<Complex> &b) {
	auto bCopy = b;
	unsigned n = 1;
	while (n < a.size() + b.size()) {
		n *= 2;
    }

	a.resize(n, 0);
	bCopy.resize(n, 0);
    FFT(a);
    FFT(bCopy);

    for (unsigned i = 0; i < n; i++) {
        a[i] *= bCopy[i];
    }
    FFT(a, true);

    for (auto& c : a) {
        c = Complex(std::round(c.real()) > 0 ? 1 : 0);
    }
}

void applySquare(std::vector<Complex> &a) {
	unsigned n = 1;
	while (n < 2*a.size()) {
		n *= 2;
    }

	a.resize(n, 0);
    FFT(a);

    for (unsigned i = 0; i < n; i++) {
        a[i] *= a[i];
    }
    FFT(a, true);

    for (auto& c : a) {
        c = Complex(std::round(c.real()) > 0 ? 1 : 0);
    }
}

std::vector<Complex> getPower(std::vector<Complex> &a, int exp) {
    std::vector<Complex> power = a;
    std::vector<Complex> result(1, 1);
    for (int e = 0; e <= 9; ++e) {
        if (exp&(1<<e)) {
            applyConvolution(result, power);
        }
        applySquare(power);
    }
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<Complex> poly(1001, 0);
    for (int i = 0; i < n; ++i) {
        int price;
        scanf("%d", &price);
        poly[price] = Complex(1);
    }

    auto powerd = getPower(poly, k);
    for (int i = 0; i < powerd.size(); ++i) {
        Long val = (Long)std::round(powerd[i].real());
        if (val != 0) {
            printf("%d ", i);
        }
    }

    return 0;
}