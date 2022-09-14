#include <iostream>

typedef long long Long;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        Long n;
        scanf("%lld", &n);

        Long a = -1, b, d;
        for (d = 1LL; (2*n-d*d-d)/(2*(d+1)) > 0; ++d)
        {
            if ((2*n-d*d-d)%(2*(d+1)) == 0)
            {
                a = (2*n-d*d-d)/(2*(d+1));
                b = a + d;
                break;
            }
        }

        if (a == -1)
            printf("IMPOSSIBLE\n");
        else
        {
            printf("%lld = %lld", n, a++);
            while (a <= b)
                printf(" + %lld", a++);
            printf("\n");
        }
    }

    return 0;
}