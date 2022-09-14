#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>

#define MOD 100003

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

std::vector<Complex>* getConvolution(std::vector<Complex>* a, std::vector<Complex>* b) {
	unsigned n = 1;
	while (n < a->size() + b->size()) {
		n *= 2;
    }

	a->resize(n, 0);
	b->resize(n, 0);
    FFT(*a);
    FFT(*b);

	std::vector<Complex>* result = new std::vector<Complex>(n);
    for (unsigned i = 0; i < n; i++) {
        result->at(i) = a->at(i) * b->at(i);
    }
    FFT(*result, true);

    for (auto iter = result->begin(); iter != result->end(); ++iter) {
        Long val = Long(std::round(iter->real())) % MOD;
        *iter = Complex(val, 0);
    }

	return result;
}

std::vector<Complex>* exps[30000];

std::vector<Complex>* getProduct(int left, int right) {
    if (left == right) {
        return exps[left];
    }

    int mid = (left + right) / 2;
    auto leftProd = getProduct(left, mid);
    auto rightProd = getProduct(mid+1, right);

    auto result = getConvolution(leftProd, rightProd);
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        exps[i] = new std::vector<Complex>();
        exps[i]->emplace_back(val%MOD, 0);
        exps[i]->emplace_back(1, 0);
    }

    auto product = getProduct(0, n-1);

    int q;
    scanf("%d", &q);
    while (q--) {
        int k;
        scanf("%d", &k);
        printf("%lld\n", Long(std::round(product->at(n-k).real())) % MOD);
    }

    return 0;
}