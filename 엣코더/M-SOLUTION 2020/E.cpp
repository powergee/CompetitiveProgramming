#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>

typedef long long Long;

int n;
int x[15], y[15], p[15];
std::map<int, int> xCount, yCount;
std::set<int> xRails, yRails;

int findNearest(int index)
{
    Long result = LLONG_MAX;
    for (int xr : xRails)
        result = std::min(result, p[index] * (Long)abs(xr - x[index]));
    for (int yr : yRails)
        result = std::min(result, p[index] * (Long)abs(yr - y[index]));
    return result;
}

Long getCurrentDistance()
{
    Long result = 0;
    for (int i = 0; i < n; ++i)
        result += findNearest(i);
    return result;
}

Long getDistance(int k)
{
    Long result = getCurrentDistance();

    if (k == 0)
        return result;
    else
    {
        Long before = result;
        for (int i = 0; i < n; ++i)
        {
            if (xRails.find(x[i]) != xRails.end() || yRails.find(y[i]) != yRails.end())
                continue;

            Long current, predict;
            
            xRails.insert(x[i]);
            predict = getCurrentDistance();
            if (before > predict)
            {
                current = getDistance(k - 1);
                result = std::min(result, current);
            }
            xRails.erase(x[i]);

            yRails.insert(y[i]);
            predict = getCurrentDistance();
            if (before > predict)
            {
                current = getDistance(k - 1);
                result = std::min(result, current);
            }
            yRails.erase(y[i]);
        }

        return result;
    }
}

int main()
{
    xRails.insert(0);
    yRails.insert(0);
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d %d", x + i, y + i, p + i);
        xCount[x[i]] += 1;
        yCount[y[i]] += 1;
    }

    Long prev = LLONG_MAX;
    for (int k = 0; k <= n; ++k)
    {
        if (prev == 0)
        {
            printf("0\n");
            continue;
        }

        Long current = getDistance(k);
        printf("%lld\n", current);
        prev = current;
    }

    return 0;
}