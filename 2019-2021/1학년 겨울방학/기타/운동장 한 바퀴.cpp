#include <iostream>

double PI = 3.141592;

int main()
{
    double d1, d2;
    std::cin >> d1 >> d2;
    printf("%.10lf", d1 * 2 + 2 * PI * d2);

    return 0;
}