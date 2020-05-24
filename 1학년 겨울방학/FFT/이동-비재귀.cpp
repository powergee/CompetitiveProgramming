#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>

typedef std::complex<double> Complex;
const double PI = acos(-1);

std::vector<Complex> x;
std::vector<Complex> y;

void FFT(std::vector<Complex>& f, bool inv)
{
    int n = f.size();
    std::vector<Complex> g = f;

    for (int i = 0; i < n; ++i)
    {
        int sz = n, shift = 0, idx = i;
        while (sz > 1)
        {
            if (idx & 1)
                shift += sz >> 1;
            idx >>= 1;
            sz >>= 1;
        }
        f[shift + idx] = g[i];
    }

    for (int i = 1; i < n; i <<= 1)
    {
        double x = inv ? PI / i : -PI / i;
        Complex w = {cos(x), sin(x)};

        for (int j = 0; j < n; j += i << 1)
        {
            Complex th = {1, 0};
            for (int k = 0; k < i; ++k)
            {
                Complex tmp = f[i + j + k] * th;
                f[i + j + k] = f[j + k] - tmp;
                f[j + k] += tmp;
                th *= w;
            }
        }
    }

    if (inv)
    {
        for (int i = 0; i < n; ++i)
        {
            f[i] /= n;
        }
    }
}

std::vector<Complex> GetConvolution(std::vector<Complex>& a, std::vector<Complex>& b)
{
    int n = 1;
    while (n <= a.size() || n <= b.size())
        n *= 2;
    n *= 2; // c의 길이가 2n - 1
    
    a.resize(n);
    b.resize(n);
    std::vector<Complex> c(n);
    Complex w(cos(2 * PI/n), sin(2 * PI/n));

    FFT(a, false);
    FFT(b, false);

    for (int i = 0; i < n; ++i)
        c[i] = a[i] * b[i];

    FFT(c, true);
    for (int i = 0; i < n; ++i)
        c[i] = Complex(round(c[i].real()), round(c[i].imag()));

    return c;
}

int main()
{
    int n;
    scanf("%d", &n);
    x.resize(2 * n);
    y.resize(2 * n);

    for (int i = 0; i < n; ++i)
    {
        int xi;
        scanf("%d", &xi);
        x[i] = x[i + n] = Complex(xi, 0);
    }

    for (int i = 0; i < n; ++i)
    {
        int yi;
        scanf("%d", &yi);
        y[n - i - 1] = Complex(yi, 0);
        y[i + n] = Complex(0, 0);
    }

    std::vector<Complex> c = GetConvolution(x, y);
    long long result = (long long)c[n - 1].real();
    for (int i = n; i < 2 * n - 1; ++i)
        result = std::max(result, (long long)c[i].real());

    printf("%lld", result);

    return 0;
}