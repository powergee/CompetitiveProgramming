#include <iostream>

int Fac(int n)
{
    int result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;
    return result;
}

int Calc(int n, int k)
{
    if (k < 0 || k > n)
        return 0;

    return Fac(n) / Fac(k) / (Fac(n - k));
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d", Calc(n, k));

    return 0;
}