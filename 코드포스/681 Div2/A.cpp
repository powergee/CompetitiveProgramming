#include <iostream>
#include <algorithm>

// bool isPrime[401];

int main()
{
    // std::fill(isPrime, isPrime+401, true);
    // isPrime[0] = isPrime[1] = false;

    // for (int i = 2; i*i < 401; ++i)
    //     if (isPrime[i])
    //         for (int j = i*i; j < 401; j += i)
    //             isPrime[j] = false;

    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 4*n; i > 2*n; i -= 2)
            printf("%d ", i);
        printf("\n");
    }

    return 0;
}