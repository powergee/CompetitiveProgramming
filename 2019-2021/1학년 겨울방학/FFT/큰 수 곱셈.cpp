#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

typedef std::complex<double> Complex;
const double PI = acos(-1);

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

void GetConvolution(std::vector<Complex>& a, std::vector<Complex>& b, std::vector<Complex>& c)
{
    int n = 1;
    while (n <= a.size() || n <= b.size())
        n *= 2;
    n *= 2;
    
    a.resize(n);
    b.resize(n);
    c.resize(n);
    Complex w(cos(2 * PI/n), sin(2 * PI/n));

    FFT(a, false);
    FFT(b, false);

    for (int i = 0; i < n; ++i)
        c[i] = a[i] * b[i];

    FFT(c, true);
    for (int i = 0; i < n; ++i)
        c[i] = Complex(round(c[i].real()), round(c[i].imag()));
}

int main()
{
    std::string a, b;
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> a >> b;

    std::vector<Complex> aExp(a.size()), bExp(b.size());

    for (int i = 0; i < a.size(); ++i)
        aExp[a.size() - i - 1] = Complex((double)(a[i] - '0'), 0);

    for (int i = 0; i < b.size(); ++i)
        bExp[b.size() - i - 1] = Complex((double)(b[i] - '0'), 0);

    std::vector<Complex> result;
    GetConvolution(aExp, bExp, result);

    for (int i = 0; i < result.size() - 1; ++i)
    {
        if (result[i].real() > 9)
        {
            result[i + 1] = Complex(result[i + 1].real() + (long long)result[i].real() / 10, 0);
            result[i] = Complex((long long)result[i].real() % 10, 0);
        }
    }

    bool print = false;
    for (int i = result.size() - 1; i >= 0; --i)
    {
        if (print)
            printf("%lld", (long long)result[i].real());
        else if ((long long)result[i].real() != 0)
        {
            print = true;
            ++i;
            continue;
        }
    }

    if (!print)
        printf("0");

    return 0;
}