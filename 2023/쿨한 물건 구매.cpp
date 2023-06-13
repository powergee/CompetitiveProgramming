#include <iostream>
#include <numeric>

long long smallest_multiple(long long total, long long div) {
    if (total < 0) {
        return 0;
    }
    return ((total / div) + ((total % div) ? 1 : 0)) * div;
}

int main() {
    long long d, p, q;
    std::cin >> d >> p >> q;
    if (p < q) {
        std::swap(p, q);
    }
    long long answer = smallest_multiple(d, q);
    for (long long x = 0; x <= std::min(d / p + 1, q); ++x) {
        answer = std::min(p * x + smallest_multiple(d - p * x, q), answer);
    }
    std::cout << answer << "\n";
    return 0;
}
