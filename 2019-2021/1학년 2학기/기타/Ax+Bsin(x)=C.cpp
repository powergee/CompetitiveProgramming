#include <iostream>
#include <cmath>
#include <algorithm>

// f(x) = Ax + Bsin(x) - C
// f'(x) = A + Bcos(x)

typedef double Real;

int A, B, C;

Real F(Real x)
{
    return A * x + B * sin(x) - C;
}

Real FPrime(Real x)
{
    return A + B * cos(x);
}

int main()
{
    scanf("%d %d %d", &A, &B, &C);

    int mod = 1;
    int smallest = std::min(A, std::min(B, C));
    for (int i = smallest; i > 0; --i)
    {
        if (A % i == 0 && B % i == 0 && C % i == 0)
        {
            mod = i;
            break;
        }
    }

    A /= mod;
    B /= mod;
    C /= mod;

    Real xFound = 0;
    for (int i = 0; i < 10000; ++i)
    {
        xFound = xFound - F(xFound) / FPrime(xFound);
    }

    printf("%.19lf", xFound);
}