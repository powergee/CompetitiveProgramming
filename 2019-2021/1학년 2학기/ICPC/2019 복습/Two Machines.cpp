#include <iostream>
#include <algorithm>
#include <queue>

std::pair<int, int> times[250];
int N;
int minTime = 0x7fffffff;

struct Assignment
{
    int aTime, bTime, pos;

    int Total() const
    {
        return std::max(aTime, bTime);
    }

    bool operator < (const Assignment& a) const
    {
        if (Total() > a.Total()) return true;
        else return pos < a.pos;
    }
};

int main()
{
    scanf("%d", &N);

    int aSum = 0, bSum = 0;
    for (int i = 0; i < N; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        times[i] = {a, b};

        aSum += a;
        bSum += b;
    }

    minTime = std::min(aSum, bSum);

    std::priority_queue<Assignment> pq;
    pq.push({0, 0, 0});

    while (!pq.empty())
    {
        auto as = pq.top();
        pq.pop();

        if (as.Total() < minTime)
        {
            if (as.pos == N)
                minTime = as.Total();

            else
            {
                pq.push({as.aTime + times[as.pos].first, as.bTime, as.pos + 1});
                pq.push({as.aTime, as.bTime + times[as.pos].second, as.pos + 1});
            }
        }
    }

    printf("%d", minTime);

    return 0;
}