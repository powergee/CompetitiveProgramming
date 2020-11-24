#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

typedef long long Long;

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        Long n;
        scanf("%lld", &n);
        Long original = n;
        
        std::vector<Long> primes;
        Long sqrtN = (Long)sqrt(n);
        for (Long p = 2; p <= sqrtN; ++p)
        {
            if (n % p == 0)
            {
                primes.push_back(p);
                n /= p;
                --p;
            }
        }
        if (n > 1)
            primes.push_back(n);

        // int count = 0;
        // Long spare = 1;
        // for (int i = 0; i < (int)primes.size(); ++i)
        // {
        //     if (primes[i] == primes[0])
        //         ++count;
        //     else
        //         spare *= primes[i];
        // }

        // printf("%d\n", count);
        // for (int i = 0; i < count-1; ++i)
        //     printf("%lld ", primes[0]);
        // printf("%lld\n", primes[0] * spare);

        std::map<Long, int> count;
        std::map<Long, int> firstIndex;
        Long maxCounter = 0;
        for (int i = 0; i < (int)primes.size(); ++i)
        {
            ++count[primes[i]];
            firstIndex[primes[i]] = std::min(firstIndex[primes[i]], i);
            if (maxCounter == 0)
                maxCounter = primes[i];
            else if (count[maxCounter] < count[primes[i]])
                maxCounter = primes[i];
        }

        int maxCount = count[maxCounter];
        printf("%d\n", maxCount);
        Long printed = 1;
        for (int i = 0; i < maxCount-1; ++i)
        {
            printf("%lld ", maxCounter);
            printed *= maxCounter;
        }
        printf("%lld\n", original / printed);
    }
    
    return 0;
}