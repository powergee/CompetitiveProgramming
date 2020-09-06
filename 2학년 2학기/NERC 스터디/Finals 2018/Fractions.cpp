#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>

int main()
{
    int n;
    scanf("%d", &n);

    std::map<int, int> pCount;
    int origin = n;
    for (int i = 2; i*i <= origin; ++i)
    {
        while (n % i == 0) 
        {
            ++pCount[i];
            n /= i;
        }
    }
    if (n != 1)
        ++pCount[n];

    if ((int)pCount.size() > 1)
    {
        auto smallest = pCount.begin();
        int denom1 = (int)pow(smallest->first, smallest->second);
        int denom2 = origin / denom1;
        int numer1, numer2 = -1;

        for (numer1 = 1; numer1 < denom1; ++numer1)
        {
            if ((numer1*denom2+1) % denom1 == 0)
            {
                numer2 = ((origin-1-numer1*denom2)/denom1);
                break;
            }
        }
        
        if (numer2 == -1)
            printf("NO");
        else
        {
            printf("YES\n2\n");
            printf("%d %d\n", numer1, denom1);
            printf("%d %d\n", numer2, denom2);
        }
    }
    else printf("NO");

    return 0;
}