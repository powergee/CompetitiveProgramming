#include <iostream>
#include <algorithm>

long long times[100001];
long long maxTime[100001];
long long timeSum[100001];
int n, s;

long long Sum(int start, int last)
{
    if (last < start)
        return 0;

    if (start == 0)
        return timeSum[last];

    else return timeSum[last] - timeSum[start - 1];
}

// return: 부른 노래의 개수, 스킵한 노래 순서
std::pair<int, int> TryToSing(int remain, int index)
{
    if (maxTime[index] != maxTime[index + 1])
        TryToSing()
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d", &n, &s);

        for (int i = 0; i < n; ++i)
            scanf("%lld", times + i);

        timeSum[0] = times[0];
        for (int i = 1; i < n; ++i)
            timeSum[i] = timeSum[i-1] + times[i];

        maxTime[0] = times[0];
        for (int i = 1; i < n; ++i)
            maxTime[i] = std::max(maxTime[i - 1], times[i]);
        
        

        printf("%d\n", maxResult.second);
    }
}