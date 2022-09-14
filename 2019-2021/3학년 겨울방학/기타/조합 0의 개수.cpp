#include <iostream>
#include <valarray>

typedef long long Long;

std::valarray<Long> countFactors(Long val) {
    Long two = 0, five = 0;
    for (Long f = 2; f <= val; f *= 2) {
        two += val / f;
    }
    for (Long f = 5; f <= val; f *= 5) {
        five += val / f;
    }
    return { two, five };
}

int main() {
    Long n, m;
    std::cin >> n >> m;
    std::valarray<Long> count = countFactors(n) - countFactors(m) - countFactors(n-m);
    std::cout << std::min(count[0], count[1]);

    return 0;
}