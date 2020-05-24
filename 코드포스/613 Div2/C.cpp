#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>

typedef long long Long;

int main()
{
    Long X;
    std::cin >> X;

    if (X == 1)
    {
        printf("1 1");
        return 0;
    }

    std::vector<Long> primes;
    primes.push_back(1);
    for (Long i = 2; i <= ceil(sqrt(X));)
    {
        if (X % i == 0)
        {
            primes.push_back(i);
            X /= i;
        }
        else ++i;
    }

    if (X != 1)
        primes.push_back(X);

    std::vector<Long> coPrimes;
    for (int i = 0; i < (int)primes.size();)
    {
        Long now = primes[i];
        int j;
        for (j = i; j < (int)primes.size() && primes[i] == primes[j]; ++j);
        int count = j - i;
        coPrimes.push_back((Long)pow(now, count));
        i = j;
    }

    Long aResult = INT64_MAX, bResult = INT64_MAX;

    for (int aCount = 1; aCount < (int)coPrimes.size(); ++aCount)
    {
        std::vector<bool> aSelect((int)coPrimes.size(), false);
        std::fill(aSelect.end() - aCount, aSelect.end(), true);

        do
        {
            Long aNow = 1, bNow = 1;

            for (int i = 0; i < (int)aSelect.size(); ++i)
            {
                if (aSelect[i])
                    aNow *= coPrimes[i];
                else bNow *= coPrimes[i];
            }

            if (std::max(aResult, bResult) > std::max(aNow, bNow))
            {
                aResult = aNow;
                bResult = bNow;
            }
        } while (std::next_permutation(coPrimes.begin(), coPrimes.end()));
    }

    std::cout << aResult << " " << bResult;

    return 0;
}