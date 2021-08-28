#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <complex>
#include <iomanip>
#define DIGIT_SEG 5

using Long = long long;
using Real = double;
using Complex = std::complex<Real>;
const Real PI = std::acos(-1.L);
const int SEG_MAX = (int)std::pow(10, DIGIT_SEG);

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
	unsigned n = 1;
	while (n <= a.size() || n <= b.size()) {
		n *= 2;
    }
	n *= 2;

	a.resize(n, 0);
	b.resize(n, 0);
    FFT(a);
    FFT(b);

	std::vector<Complex> result(n);
    for (unsigned i = 0; i < n; i++) {
        result[i] = a[i] * b[i];
    }
    FFT(result, true);

	return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Complex> nums[2];
    for (int i = 0; i < 2; ++i) {
        std::string exp;
        std::cin >> exp;
        std::reverse(exp.begin(), exp.end());
        for (int j = 0; j < exp.size(); j += DIGIT_SEG){
            int seg = 0, pow = 1;
            for (int k = 0; j+k < exp.size() && k < DIGIT_SEG; ++k) {
                seg += (exp[j+k]-'0') * pow;
                pow *= 10;
            }
            nums[i].push_back(seg);
        }
    }

    std::vector<Complex> conv = getConvolution(nums[0], nums[1]);
    std::vector<Long> result(conv.size(), 0);

    for (int i = 0; i < conv.size(); ++i) {
        result[i] += (Long)std::round(conv[i].real());
        if (result[i] >= SEG_MAX) {
            while (result.size()-1 < i+1) {
                result.push_back(0);
            } 
            result[i+1] += result[i] / SEG_MAX;
            result[i] %= SEG_MAX;
        }
    }

    for (int i = result.size()-1; result[i] >= SEG_MAX; ++i) {
        while (result.size()-1 < i+1) {
            result.push_back(0);
        }
        result[i+1] += result[i] / SEG_MAX;
        result[i] %= SEG_MAX;
    }

    std::reverse(result.begin(), result.end());
    int start = 0;
    while (start < result.size() && result[start] == 0) {
        ++start;
    }
    
    if (start == result.size()) {
        std::cout << "0";
    } else {
        for (int i = start; i < result.size(); ++i) {
            if (i != start) {
                std::cout << std::setfill('0') << std::setw(DIGIT_SEG) << result[i];
            } else {
                std::cout << result[i];
            }
        }
    }
    

    return 0;
}