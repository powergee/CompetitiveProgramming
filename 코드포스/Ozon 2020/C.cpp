#include <iostream>
#include <vector>

typedef long long Long;

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    if (n > m)
    {
        printf("0");
    }
    else
    {
        std::vector<Long> vec(n);
        for (int i = 0; i < n; ++i)
            scanf("%lld", &vec[i]);

        Long result = 1;

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                result *= abs(vec[i] - vec[j]);
                result %= m;

                if (result == 0)
                    goto END_OF_LOOP;
            }
        } END_OF_LOOP:

        printf("%lld", result);
    }

    return 0;
}