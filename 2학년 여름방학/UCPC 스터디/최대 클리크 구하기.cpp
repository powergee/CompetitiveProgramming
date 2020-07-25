#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    int n;
    scanf("%d", &n);

    std::vector<std::pair<int, int>> intervals, points;
    for (int i = 0; i < n; ++i)
    {
        int s, e;
        scanf("%d %d", &s, &e);
        intervals.emplace_back(s, e);
        points.emplace_back(s, -1);
        points.emplace_back(e, 1);
    }
    std::sort(points.begin(), points.end());

    int maxCount = 0;
    int maxPoint = 0;
    int currCount = 0;
    for (int i = 0; i < 2*n; ++i)
    {
        currCount -= points[i].second;
        if (currCount > maxCount)
        {
            maxCount = currCount;
            maxPoint = points[i].first;
        }
    }

    std::vector<int> vertexes;
    for (int i = 0; i < n; ++i)
    {
        int s = intervals[i].first;
        int e = intervals[i].second;

        if (s <= maxPoint && maxPoint <= e)
            vertexes.push_back(i+1);
    }

    printf("%d\n", maxCount);
    for (int i = 0; i < maxCount; ++i)
        printf("%d ", vertexes[i]);

    return 0;
}