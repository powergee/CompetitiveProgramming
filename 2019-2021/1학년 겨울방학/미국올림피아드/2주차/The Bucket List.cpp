#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#define START 1
#define END -1
typedef std::tuple<int, int, int> Work;

std::vector<Work> times;

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int s, t, b;
        scanf("%d %d %d", &s, &t, &b);
        times.push_back(std::make_tuple(s, START, b));
        times.push_back(std::make_tuple(t, END, b));
    }

    std::sort(times.begin(), times.end());

    int buckets = 0;
    int maxBuckets = -1;

    for (Work& w : times)
    {
        int time, isStart, usage;
        std::tie(time, isStart, usage) = w;

        buckets += usage * isStart;
        maxBuckets = std::max(maxBuckets, buckets);
    }

    printf("%d", maxBuckets);

    return 0;
}