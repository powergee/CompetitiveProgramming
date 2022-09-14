#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

typedef long long Long;

int GetCCW(int ax, int ay, int bx, int by, int cx, int cy)
{
    Long k = (Long)(bx - ax) * (cy - ay) - (Long)(cx - ax) * (by - ay);
    if (k > 0)
        return 1;
    if (k == 0)
        return 0;
    else return -1;
};

struct Point
{
    int X, Y;

    bool operator < (const Point& p) const
    {
        int ccw = GetCCW(0, 0, X, Y, p.X, p.Y);
        if (ccw)
            return ccw > 0;
        return 0;
    }

    bool operator == (const Point& p) const
    {
        return GetCCW(0, 0, X, Y, p.X, p.Y) == 0;
    }
};

int GetCCW(const Point& p1, const Point& p2, const Point& p3)
{
    return GetCCW(p1.X, p1.Y, p2.X, p2.Y, p3.X, p3.Y);
}

int N, now;
bool vis[100005];
std::vector<Point> down[100005];
std::vector<int> downIndex[100005];
std::vector<int> in[1000006];
std::vector<int> out[1000006];

struct Down
{
    int n;
    bool operator < (const Down& d) const
    {
        int t1 = std::upper_bound(downIndex[n].begin(), downIndex[n].end(), now) - downIndex[n].begin();
        int t2 = std::upper_bound(downIndex[d.n].begin(), downIndex[d.n].end(), now) - downIndex[d.n].begin();

        Point a = down[n][t1 - 1];
        Point b = down[n][t1];
        Point p = down[d.n][t2 - 1];
        Point q = down[d.n][t2];

        if (downIndex[n][t1 - 1] <= downIndex[d.n][t2 - 1])
            return GetCCW(a, b, p) < 0;
        else return GetCCW(p, q, a) > 0;
    }
};

int main()
{
    scanf("%d", &N);

    for (int i = 1; i <= N; ++i)
    {
        int m;
        scanf("%d", &m);
        std::vector<Point> points;

        for (int j = 0; j < m; ++j)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            points.push_back({ x, y });
        }

        int p = 0, q = 0;
        for (int j = 0; j < m; ++j)
        {
            if (GetCCW({ 0, 0 }, points[p], points[j]) > 0 || (GetCCW({ 0, 0 }, points[p], points[j]) == 0 && points[p].Y > points[j].Y))
                p = j;
            if (GetCCW({ 0, 0 }, points[q], points[j]) < 0 || (GetCCW({ 0, 0 }, points[q], points[j]) == 0 && points[q].Y > points[j].Y))
                q = j;
        }

        for (int j = p; ; j = (j + 1) % m)
        {
            down[i].push_back(points[j]);
            if (j == q)
                break;
        }

        std::reverse(down[i].begin(), down[i].end());
    }

    std::vector<Point> all;
    for (int i = 1; i <= N; ++i)
        for (Point& p : down[i])
            all.push_back(p);

    std::sort(all.begin(), all.end());
    all.erase(std::unique(all.begin(), all.end()), all.end());

    for (int i = 1; i <= N; ++i)
    {
        for (Point& p : down[i])
            downIndex[i].push_back(std::lower_bound(all.begin(), all.end(), p) - all.begin() + 1);
    }

    for (int i = 1; i <= N; ++i)
    {
        in[downIndex[i][0]].push_back(i);
        out[downIndex[i].back()].push_back(i);
    }

    std::set<Down> s;

    for (int i = 1; i < all.size(); ++i)
    {
        for (int j : out[i])
            s.erase({ j });

        now = i;

        for (int j : in[i])
            s.insert({ j });

        if (!s.empty())
            vis[s.begin()->n] = 1;
    }

    int answer = 0;
    for (int i = 1; i <= N; ++i)
        if (!vis[i])
            ++answer;

    printf("%d", answer);

    return 0;
}