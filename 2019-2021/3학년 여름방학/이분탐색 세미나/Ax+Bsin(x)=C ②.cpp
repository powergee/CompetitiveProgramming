#include <iostream>
#include <cmath>

int main() {
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);

    double left = 0, right = (b+c)/a + 1;
    for (int i = 0; i < 10000; ++i) {
        double x = (left+right) / 2;
        if (a*x + b*sin(x) - c > 0) {
            right = x;
        } else {
            left = x;
        }
    }

    printf("%.10lf", left);

    return 0;
}