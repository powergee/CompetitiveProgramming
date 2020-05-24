#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long long Long;
std::pair<Long, Long> points[20];

Long GetVecLength(std::pair<Long, Long> vec)
{
    return vec.first * vec.first + vec.second * vec.second;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%lld %lld", &points[i].first, &points[i].second);

        std::vector<bool> select(n, false);
        std::fill(select.end() - n/2, select.end(), true);
        std::pair<Long, Long> minSum = {1e7, 1e7};
        
        do
        {
            std::pair<Long, Long> sum = {0, 0};
            for (int i = 0; i < n; ++i)
            {
                if (select[i])
                    sum.first += points[i].first, sum.second += points[i].second;
                else sum.first -= points[i].first, sum.second -= points[i].second;
            }

            if (GetVecLength(sum) < GetVecLength(minSum))
                minSum = sum;
        } while (std::next_permutation(select.begin(), select.end()));

        printf("%.10lf\n", sqrt(GetVecLength(minSum)));
    }

    return 0;
}