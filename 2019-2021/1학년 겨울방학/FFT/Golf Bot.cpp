#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <algorithm>

const double PI = acos(-1);
typedef std::complex<double> Complex;

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

std::unordered_set<int> dSet;

int main()
{
    int n, m;
    scanf("%d", &n);
    std::vector<Complex> a1(200001, {0, 0});
    std::vector<Complex> a2(200001, {0, 0});

    for (int i = 0; i < n; ++i)
    {
        int ki;
        scanf("%d", &ki);
        a1[ki] = {1, 0};
        a2[ki] = {1, 0};
    }
    a1[0] = a2[0] = {1, 0};

    scanf("%d", &m);

    for (int i = 0; i < m; ++i)
    {
        int di;
        scanf("%d", &di);
        dSet.insert(di);
    }

    std::vector<Complex> aa;
    GetConvolution(a1, a2, aa);

    int count = 0;
    for (int i = 1; i < aa.size(); ++i)
        if (aa[i].real() >= 1 && dSet.find(i) != dSet.end())
            ++count;

    printf("%d", count);

    return 0;
}