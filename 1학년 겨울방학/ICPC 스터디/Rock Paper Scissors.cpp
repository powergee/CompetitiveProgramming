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

std::vector<Complex> GetConvolution(std::vector<Complex>& a, std::vector<Complex>& b)
{
    int n = 1;
    while (n <= a.size() || n <= b.size())
        n *= 2;
    n *= 2;
    
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

void Match(char mCh, char yCh, std::string& M, std::string& Y, std::vector<int>& result)
{
    std::vector<Complex> mVec(M.size()), yVec(Y.size());

    for (int i = 0; i < M.size(); ++i)
        mVec[i] = Complex((mCh == M[i] ? 1 : 0), 0);

    for (int i = 0; i < Y.size(); ++i)
        yVec[i] = Complex((yCh == Y[i] ? 1 : 0), 0);

    std::vector<Complex> c = GetConvolution(mVec, yVec);

    for (int i = 0; i < M.size(); ++i)
    {
        //std::cout << (int)c[i].real() << ' ';
        result[i] += (int)c[i].real();
    }
    //std::cout << '\n';
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::string M, Y;
    std::cin >> M >> Y;
    std::reverse(M.begin(), M.end());

    std::vector<int> result(M.size());
    std::fill(result.begin(), result.end(), 0);
    Match('S', 'R', M, Y, result);
    Match('R', 'P', M, Y, result);
    Match('P', 'S', M, Y, result);

    std::cout << *std::max_element(result.begin(), result.end());

    return 0;
}