#include <iostream>
#include <algorithm>

bool isPrime[10001];

int main()
{
    std::fill(isPrime, isPrime+10001, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i*i < 10001; ++i)
        if (isPrime[i])
            for (int j = i*i; j < 10001; j += i)
                isPrime[j] = false;

    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        int left = n/2;
        int right = n/2;
        
        for (int i = 0; i < n/2; ++i)
        {
            if (isPrime[left] && isPrime[right])
                break;
            --left;
            ++right;
        }
            
        printf("%d %d\n", left, right);
    }
}