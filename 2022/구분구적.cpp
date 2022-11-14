#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

typedef double Real;

int main() {
    int n;
    std::cin >> n;

    std::vector<Real> coeff(n+1);
    for (int i = 0; i <= n; ++i) {
        std::cin >> coeff[n-i];
    }

    int k;
    std::cin >> k;
    k = std::min(k, 100'000);

    auto f = [&](Real x) {
        Real value = 0;
        for (int i = 0; i <= n; ++i) {
            value += std::pow(x, 2*i) * coeff[i];
        }
        return value;
    };

    auto fp = [&](Real x) {
        Real value = 0;
        for (int i = 1; i <= n; ++i) {
            value += std::pow(x, 2*i-1) * coeff[i] * (2*i);
        }
        return value;
    };

    // Newton-Raphson
    Real root = 1;
    for (int i = 0; i < 1'000'000; ++i) {
        Real next = root - f(root)/fp(root);
        Real prev = root;
        root = next;
        if (std::abs(next-prev) <= 1e-8) {
            break;
        }
    }
    root = std::abs(root);
    
    assert(root <= 32);
    Real start = -root;
    Real interval = root*2 / k;
    Real answer = 0;

    for (int i = 0; i < k; ++i) {
        answer += f(start + (2*i+1)*(interval/2));
    }
    printf("%.10lf", (double)std::abs(answer*interval));

    return 0;
}