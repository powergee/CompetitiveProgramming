#include <iostream>
#include <cmath>

int main() {
    double x;
    std::cin >> x;
    printf("%.10lf", sqrt(x * (12800000 + x)));

    return 0;
}