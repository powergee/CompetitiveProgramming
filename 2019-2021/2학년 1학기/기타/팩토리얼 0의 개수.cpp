#include <iostream>
#include <algorithm>

int CountPrime(int n, int p)
{
    int count = 0;
    while (n % p == 0)
    {
        ++count;
        n /= p;
    }
    return count;
}

int main()
{
    int n, two = 0, five = 0;
    scanf("%d", &n);

    for (int i = 2; i <= n; ++i)
    {
        two += CountPrime(i, 2);
        five += CountPrime(i, 5);
    }

    printf("%d", std::min(two, five));

    return 0;
}