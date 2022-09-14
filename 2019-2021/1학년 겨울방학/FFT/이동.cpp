#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>

typedef std::complex<double> Complex;
const double PI = acos(-1);

std::vector<Complex> x;
std::vector<Complex> y;

void FFT(std::vector<Complex>& f, Complex w)
{
    int n = f.size();
    if (n == 1)
        return;

    std::vector<Complex> even(n/2), odd(n/2);
    for (int i = 0; i < n; ++i)
    {
        if (i % 2)
            odd[i/2] = f[i];
        else
            even[i/2] = f[i];
    }

    FFT(even, w * w);
    FFT(odd, w * w);

    Complex wp(1, 0);
    for (int i = 0; i < n / 2; ++i)
    {
        f[i] = even[i] + wp * odd[i];
        f[i + n/2] = even[i] - wp * odd[i];
        wp *= w;
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

    FFT(a, w);
    FFT(b, w);

    for (int i = 0; i < n; ++i)
        c[i] = a[i] * b[i];

    FFT(c, Complex(1, 0) / w);
    for (int i = 0; i < n; ++i)
    {
        c[i] /= Complex(n, 0);
        c[i] = Complex(round(c[i].real()), round(c[i].imag()));
    }

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