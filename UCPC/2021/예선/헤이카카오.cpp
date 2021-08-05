#include <iostream>

int main() {
    long double a, d, k;
    std::cin >> a >> d >> k;

    long double singleTime = a;
    long double basisProb = 1;
    long double answer = 0;
    while (d < 100) {
        answer += basisProb * singleTime * (d/100.0);
        basisProb *= 1-(d/100.0);
        d *= 1+(k/100.0);
        singleTime += a;
    }
    answer += basisProb * singleTime;

    std::cout.precision(17);
    std::cout << answer;

    return 0;
}