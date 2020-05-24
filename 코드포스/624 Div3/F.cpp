#include <iostream>
#include <algorithm>

typedef long long Long;

std::pair<Long, Long> points[200000];
int n;

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%lld", &points[i].second);

    for (int i = 0; i < n; ++i)
        scanf("%lld", &points[i].first);

    std::sort(points, points + n);
    
    int negCount = 0;
    Long negSum = 0;
    Long distSum = 0;
    for (int i = 0; i < n; ++i)
    {
        if (points[i].first < 0)
        {
            int last = i;
            while (n > last + 1 && points[last + 1].first == points[i].first)
                ++last;
            for (int left = i; left <= last; ++left)
            {
                ++negCount;
                negSum += -points[left].second;
                for (int right = left; right <= last; ++right)
                {
                    distSum += std::abs(points[left].second - points[right].second);
                }
            }
        }
        else if (points[i].first == 0)
            continue;
        else
        {
            int last = i;
            while (n > last + 1 && points[last + 1].first == points[i].first)
                ++last;
            for (int left = i; left <= last; ++left)
            {
                distSum += negSum + points[left].second * negCount;
                for (int right = left; right <= last; ++right)
                {
                    distSum += std::abs(points[left].second - points[right].second);
                }
            }
        }
    }

    printf("%lld", distSum);

    return 0;
}