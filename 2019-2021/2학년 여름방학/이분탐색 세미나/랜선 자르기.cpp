#include <iostream>
#include <algorithm>

typedef long long Long;
Long k, n;
Long lan[10000];

Long countSegments(Long length)
{
    Long count = 0;
    for (int i = 0; i < k; ++i)
        count += lan[i] / length;
    
    return count;
}

int main()
{
    scanf("%lld %lld", &k, &n);

    Long maxLength = 0;
    for (int i = 0; i < k; ++i)
    {
        scanf("%lld", lan+i);
        maxLength = std::max(maxLength, lan[i]);
    }
    
    Long left = 1, right = maxLength + 1;
    while (left+1 < right)
    {
        Long mid = (left + right) / 2;
        if (n <= countSegments(mid))
            left = mid;
        else
            right = mid;
    }

    printf("%lld", left);

    return 0;
}