#include <iostream>

int n, m;
bool sieve[1001];

int main()
{
    scanf("%d %d", &n, &m);

    while (m--)
    {
        int k;
        scanf("%d", &k);
        
        for (int i = 1; k*i <= n; ++i)
            sieve[k*i] = true;
    }

    long long sum = 0;
    for (int i = 1; i <= n; ++i)
        if (sieve[i])
            sum += i;

    std::cout << sum;

    return 0;
}