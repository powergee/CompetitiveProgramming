#include <iostream>
#include <set>
#include <algorithm>

typedef long long Long;
int n;
Long jobs[100000];

inline int toBlock(int jobIndex, Long interval)
{
    return jobs[jobIndex] / interval + (jobs[jobIndex] % interval > 0 ? 1 : 0);
}

bool ableToSchedule(Long interval)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        if (right - left == n-1)
        {
            int firstTask = toBlock(left++, interval);
            if (firstTask != 1)
                return false;
        }
        else if (right == left)
        {
            if (toBlock(left++, interval) <= 2)
                return true;
            else return false;
        }
        else
        {
            int longest = toBlock(right--, interval);
            for (int i = 0; i < longest - 2; ++i)
            {
                int taskForOther = toBlock(left++, interval);
                if (taskForOther != 1)
                    return false;
            }
        }
    }
    return true;
}

Long searchMinInterval(Long left, Long right)
{
    if (left == right)
        return left;

    Long mid = (left + right) / 2;
    if (ableToSchedule(mid))
        return searchMinInterval(left, mid);
    else
        return searchMinInterval(mid + 1, right);
}

int main()
{
    scanf("%d", &n);
    Long max = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%lld", jobs + i);
        max = std::max(max, jobs[i]);
    }
    std::sort(jobs, jobs + n);

    std::cout << searchMinInterval(1, max);

    return 0;
}