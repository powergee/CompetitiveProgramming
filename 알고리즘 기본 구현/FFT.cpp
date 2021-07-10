#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>

using Real = long double;
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

std::vector<Complex> getConvolution(std::vector<Complex> &a, std::vector<Complex> &b) {
	auto aCopy = a;
	auto bCopy = b;
	unsigned n = 1;
	while (n <= a.size() || n <= b.size()) {
		n *= 2;
    }
	n *= 2;

	aCopy.resize(n, 0);
	bCopy.resize(n, 0);
    FFT(aCopy);
    FFT(bCopy);

	std::vector<Complex> result(n);
    for (unsigned i = 0; i < n; i++) {
        result[i] = aCopy[i] * bCopy[i];
    }
    FFT(result, true);

	return result;
}