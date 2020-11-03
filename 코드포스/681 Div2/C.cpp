#include <iostream>
#include <algorithm>

typedef long long Long;

std::pair<int, int> delTime[200000];
std::pair<int, int> goTime[200000];
int goTimeVal[200000];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &delTime[i].first);
            delTime[i].second = i;
        }
        
        Long goSum = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", goTimeVal+i);
            goSum += goTimeVal[i];
        }
        
        std::sort(delTime, delTime + n);
        for (int i = 0; i < n; ++i)
        {
            int idx = delTime[i].second;
            goTime[i].first = goTimeVal[idx];
            goTime[i].second = idx;
        }
        
        Long answer = goSum;
        for (int i = 0; i < n; ++i)
        {
            goSum -= goTime[i].first;
            Long current = std::max(goSum, (Long)delTime[i].first);
            answer = std::min(current, answer);
        }

        printf("%lld\n", answer);
    }

    return 0;
}