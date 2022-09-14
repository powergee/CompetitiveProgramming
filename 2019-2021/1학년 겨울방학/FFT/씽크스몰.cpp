#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

typedef std::complex<long double> Complex;
const long double PI = acos(-1.L);

inline unsigned bitreverse(const unsigned n, const unsigned k) {
    unsigned r, i;
    for (r = 0, i = 0; i < k; ++i)
        r |= ((n >> i) & 1) << (k - i - 1);
    return r;
}
 
void FFT(std::vector<Complex> &a, bool is_reverse=false) {
    const unsigned n = a.size(), k = __builtin_ctz(n);
    unsigned s, i, j;
    for (i = 0; i < n; i++) {
        j = bitreverse(i, k);
        if (i < j)
            swap(a[i], a[j]);
    }
    for (s = 2; s <= n; s *= 2) {
        std::vector<Complex> w(s/2);
        for (i = 0; i < s/2; i++) {
            long double t = 2*PI*i/s * (is_reverse? -1 : 1);
            w[i] = Complex(cos(t), sin(t));
        }
        for (i = 0; i < n; i += s) {
            for (j = 0; j < s/2; j++) {
                Complex tmp = a[i + j + s/2] * w[j];
                a[i + j + s/2] = a[i + j] - tmp;
                a[i + j] += tmp;
            }
        }
    }
    if (is_reverse)
        for (i = 0; i < n; i++)
            a[i] /= n;
}

void GetConvolution(std::vector<Complex>& a, std::vector<Complex>& b)
{
    const unsigned n = a.size();
    FFT(a);
    FFT(b);

    for (unsigned i = 0; i < n; ++i)
        a[i] *= b[i];

    FFT(a, true);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    unsigned n, m;
    std::cin >> n >> m;
    ++n, ++m;

    unsigned np = 1;
    for (; np < 2 * std::max(n, m) - 1; np *= 2);

    std::vector<Complex> f(np, 0), g(np, 0);

    for (unsigned i = 0; i < n; ++i)
        std::cin >> f[i];

    for (unsigned i = 0; i < m; ++i)
        std::cin >> g[i];

    GetConvolution(f, g);

    unsigned long long result = 0;
    for (unsigned i = 0; i < n + m - 1; ++i)
        result ^= (unsigned long long)(f[i].real() + (f[i].real() > 0 ? 0.5L : -0.5L));

    std::cout << result;

    return 0;
}