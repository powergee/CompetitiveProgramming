#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>

int divCases[500001];

typedef std::complex<double> Complex;
const double PI = acos(-1);

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
    while (n <= (int)a.size() || n <= (int)b.size())
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
    for (int i = 1; i <= 500000; ++i)
    {
        int sqrt_i = sqrt(i);
        for (int d = 1; d <= sqrt_i; ++d)
            if (i % d == 0)
                divCases[i] += 2;

        if (sqrt_i * sqrt_i == i)
            --divCases[i];
    }

    std::vector<Complex> a(500000, {0, 0}), b(500000, {0, 0});
    for (int i = 1; i <= 500000; ++i)
    {
        a[i] = Complex(divCases[i], 0);
        b[i] = Complex(divCases[i], 0);
    }

    std::vector<Complex> conv = GetConvolution(a, b);

    std::ofstream result("Intervals.txt");
    result << "int data[] = { ";
    int currMax = -1;
    for (int i = 1; i <= 500000; ++i)
    {
        currMax = std::max(currMax, (int)conv[i].real());
        if (i % 9 == 0)
        {
            result << currMax << ",";
            currMax = -1;
        }
    }
    if (currMax != -1)
        result << currMax << ",";
    result << "};" << std::endl;
    result.close();

    std::ofstream divResult("Div.txt");
    divResult << "int divCases[] = {";
    for (int i = 0; i <= 500001; ++i)
        divResult << divCases[i] << ",";
    divResult << "};";
    divResult.close();

    return 0;
}