#include <iostream>

int main()
{
    long long N, L;
    scanf("%lld %lld", &N, &L);

    for (long long l = L; l <= 100; ++l)
    {
        long long numer = 2*N - l*l + l;
        long long denum = 2*l;

        if (numer % denum == 0 && numer >= 0)
        {
            long long a = numer / denum;
            for (long long i = a; i <= a+l-1; ++i)
                printf("%lld ", i);
            return 0;
        }
    }
    printf("-1");

    return 0;
}