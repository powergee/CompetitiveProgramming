#include <iostream>

int GetMod(int base, int exp, int mod)
{
    if (exp == 0)
        return 1 % mod;
    else if (exp == 1)
        return base % mod;

    int mid = exp / 2;
    return (int)(((long long)GetMod(base, mid, mod) * GetMod(base, exp - mid, mod)) % mod);
}

int main()
{
    int a, e, m;
    scanf("%d %d %d", &a, &e, &m);
    printf("%d", GetMod(a, e, m));

    return 0;
}