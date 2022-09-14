#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>

const double PI = acos(-1);

typedef std::complex<double> Complex;

std::vector<Complex> path[100];
std::vector<Complex> tele[100];

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
    int n, l, m;
    long long w;
    scanf("%d %d %d %lld", &n, &l, &m, &w);

    for (int row = 0; row < m; ++row)
    {
        path[row].resize(n);
        for (int col = 0; col < n; ++col)
        {
            int input;
            scanf("%d", &input);
            path[row][col] = Complex(input, 0);
        }
    }

    for (int row = 0; row < m; ++row)
    {
        tele[row].resize(l);
        for (int col = 0; col < l; ++col)
        {
            int input;
            scanf("%d", &input);
            tele[row][l - col - 1] = Complex(input, 0);
        }
    }

    std::vector<Complex> sum;
    for (int row = 0; row < m; ++row)
    {
        std::vector<Complex> c;
        GetConvolution(path[row], tele[row], c);

        if (sum.size() != c.size())
            sum.resize(c.size());

        for (int i = 0; i < c.size(); ++i)
            sum[i] += c[i];
    }

    int count = 0;
    for (int i = l - 1; i <= n - 1; ++i)
        if ((long long)sum[i].real() > w)
            ++count;

    printf("%d", count);

    return 0;
}