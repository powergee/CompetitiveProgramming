#include <iostream>
#include <algorithm>
#include <vector>

long long times[100001];
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

int TryToSing(long long s)
{
    for (int i = 0; i < n; ++i)
    {
        if (s < timeSum[i])
            return i;
    }
    return n;
}

int TryToSing(long long s, int skip)
{
    for (int i = 0; i < skip; ++i)
    {
        if (s < Sum(0, i))
            return i;
    }

    s -= Sum(0, skip - 1);

    for (int i = skip + 1; i < n; ++i)
    {
        if (s < Sum(skip + 1, i))
            return (i - 1);
    }

    return n - 1;
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

        std::vector<int> maxPoints;
        maxPoints.push_back(0);

        for (int i = 1; i < n - 1; ++i)
        {
            if (times[i-1] <= times[i] && times[i] >= times[i+1])
                maxPoints.push_back(i);
        }
        
        int noSkip = TryToSing(s);
        std::pair<int, int> maxResult = {noSkip, 0};

        for (int i : maxPoints)
        {
            int current = TryToSing(s, i);
            if (maxResult.first < current)
            {
                maxResult.first = current;
                maxResult.second = i + 1;
            }
        }

        printf("%d\n", maxResult.second);
    }
}