#include <iostream>
#include <climits>

typedef long long Long;
std::pair<Long, Long> polices[500000];
std::pair<Long, Long> theif;
int n;

bool isCaptured(std::pair<Long, Long> point, Long elapsed)
{
    for (int i = 0; i < n; ++i)
    {
        if (point.second <= -point.first + polices[i].first + polices[i].second + elapsed &&
            point.second <= point.first - polices[i].first + polices[i].second + elapsed &&
            point.second >= point.first - polices[i].first + polices[i].second - elapsed &&
            point.second >= -point.first + polices[i].first + polices[i].second - elapsed)
            return true;
    }
    return false;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%lld %lld", &polices[i].first, &polices[i].second);
    scanf("%lld %lld", &theif.first, &theif.second);

    const Long elapsed = INT32_MAX;
    if (isCaptured({theif.first + elapsed, theif.second}, elapsed) &&
        isCaptured({theif.first - elapsed, theif.second}, elapsed) &&
        isCaptured({theif.first, theif.second + elapsed}, elapsed) &&
        isCaptured({theif.first, theif.second - elapsed}, elapsed))
        printf("NO");
    else printf("YES");

    return 0;
}