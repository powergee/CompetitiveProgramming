#include <iostream>
#include <algorithm>

bool isPrime[230];

int main()
{
    int n;
    scanf("%d", &n);

    std::fill(isPrime, isPrime + 230, true);

    for (int i = 2; i < 230; ++i)
        if (isPrime[i])
            for (int j = 2; i * j < 230; ++j)
                isPrime[i*j] = false;

    printf("%d\n", n);
    for (int i = 1; i < 230 && n > 0; ++i)
    {
        if (isPrime[i])
        {
            printf("%d ", i);
            --n;
        }
    }

    return 0;
}