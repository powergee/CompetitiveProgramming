#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>

int main() {
    double a, b;
    scanf("%lf %lf", &a, &b);

    double coeff = (1.0/sqrt(a*a+b*b));
    printf("%.10lf %.10lf", coeff*a, coeff*b);

    return 0;
}