#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>

int n;
int arr[1000000];
std::map<int, int> count;
bool isPrime[1000001];

void factorize(int val, std::set<int>& primes)
{
    if (val == 1)
        return;

    if (isPrime[val])
    {
        primes.insert(val);
        return;
    }

    int sqrt = (int)std::round(std::sqrt(val));
    if (sqrt*sqrt == val)
    {
        factorize(sqrt, primes);
        return;
    }
    
    for (int i = 2; i <= sqrt; ++i)
    {
        if (val % i == 0)
        {
            primes.insert(i);
            factorize(val / i, primes);
            return;
        }
    }
}

int main()
{
    std::fill(isPrime, isPrime+1000001, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i*i < 1000001; ++i)
        if (isPrime[i])
            for (int j = i*i; j < 1000001; j += i)
                isPrime[j] = false;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", arr+i);
        std::set<int> primes;
        factorize(arr[i], primes);

        for (int p : primes)
            ++count[p];
    }
    
    int max = 0;
    for (auto p : count)
        max = std::max(max, p.second);

    if (max <= 1)
        printf("pairwise coprime");
    else if (max < n)
        printf("setwise coprime");
    else
        printf("not coprime");
}