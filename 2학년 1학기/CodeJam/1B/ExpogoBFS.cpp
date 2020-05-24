#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <set>

typedef long long Long;

struct QueueEle
{
    int exp;
    std::pair<Long, Long> point;
    std::string path;
};

bool Contains(std::set<std::pair<Long, Long>> s, std::pair<Long, Long> p)
{
    return s.find(p) != s.end();
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int c = 1; c <= T; ++c)
    {
        int x, y, xLimit, yLimit;
        scanf("%d%d", &x, &y);
        xLimit = 16 * abs(x);
        yLimit = 16 * abs(y);

        bool xEven = x % 2 == 0;
        bool yEven = y % 2 == 0;

        if (xEven == yEven)
            printf("Case #%d: %s\n", c, "IMPOSSIBLE");
        else
        {
            std::queue<QueueEle> q;
            std::set<std::pair<Long, Long>> visited;
            q.push({ 0, {0, 0}, "" });
            bool success = false;

            while (!q.empty())
            {
                auto now = q.front();
                q.pop();

                if (Contains(visited, now.point))
                    continue;
                visited.insert(now.point);

                if (now.point.first == x && now.point.second == y)
                {
                    success = true;
                    printf("Case #%d: ", c);
                    std::cout << now.path << '\n';
                    break;
                }

                int dist = 1 << now.exp;
                if (!Contains(visited, { now.point.first + dist, now.point.second }) && abs(now.point.first + dist) <= xLimit)
                    q.push({ now.exp + 1, {now.point.first + dist, now.point.second}, now.path + 'E' });

                if (!Contains(visited, { now.point.first - dist, now.point.second }) && abs(now.point.first - dist) <= xLimit)
                    q.push({ now.exp + 1, {now.point.first - dist, now.point.second}, now.path + 'W' });

                if (!Contains(visited, { now.point.first, now.point.second + dist }) && abs(now.point.second + dist) <= yLimit)
                    q.push({ now.exp + 1, {now.point.first, now.point.second + dist}, now.path + 'N' });

                if (!Contains(visited, { now.point.first, now.point.second - dist }) && abs(now.point.second - dist) <= yLimit)
                    q.push({ now.exp + 1, {now.point.first, now.point.second - dist}, now.path + 'S' });
            }

            if (!success)
            {
                printf("Case #%d: %s\n", c, "IMPOSSIBLE");
            }
        }
    }

    return 0;
}