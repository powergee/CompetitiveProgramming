#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

struct Point
{
    Long X, Y;
    int Index;

    Point(Long x, Long y, int index) : X(x), Y(y), Index(index) {}
    Point(Long x, Long y) : Point(x, y, -1) {}
};

Point anglePivot(-1, -1);

Long Dist(const Point& p1, const Point& p2)
{
    return (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
}

Long CCW(const Point& p1, const Point& p2, const Point& p3)
{
    return p1.X * p2.Y + p2.X * p3.Y + p3.X * p1.Y
        - p1.Y * p2.X - p2.Y * p3.X - p3.Y * p1.X;
}

bool CompareByAxis(const Point& p1, const Point& p2)
{
    if (p1.X < p2.X)
        return true;
    else if (p1.X == p2.X)
        return p1.Y < p2.Y;
    else return false;
}

bool CompareByAngle(const Point& p1, const Point& p2)
{
    Long ccw = CCW(anglePivot, p1, p2);
    if (ccw > 0)
        return true;
    else if (ccw == 0)
        return Dist(anglePivot, p1) < Dist(anglePivot, p2);
    else return false;
}

void TryToPush(const Point& p, std::vector<Point>& hull, std::vector<Point>& points)
{
    int size = hull.size();
    Long ccw = CCW(hull[size - 2], hull[size - 1], p);

    while (ccw < 0)
    {
        hull.pop_back();
        size = hull.size();
        ccw = CCW(hull[size - 2], hull[size - 1], p);
    }

    if (ccw > 0)
        hull.push_back(p);

    else if (ccw == 0)
    {
        if (Dist(hull[size - 2], p) > Dist(hull[size - 2], hull[size - 1]))
            hull[size - 1] = p;
    }
}

void GetConvexHull(std::vector<Point>& points, std::vector<Point>& result)
{
    if (points.size() <= 2)
    {
        for (Point& p : points)
            result.push_back(p);
        return;
    }

    anglePivot = points[0];
    std::sort(points.begin(), points.end(), CompareByAngle);

    result.push_back(points[0]);
    result.push_back(points[1]);

    for (int i = 2; i < (int)points.size(); ++i)
        TryToPush(points[i], result, points);
    TryToPush(points[0], result, points);
    result.pop_back();

    if (result.size() == 1 && !(result[0].X == points.back().X && result[0].Y == points.back().Y))
        result.push_back(points.back());
}

bool IsInside(Point& p, std::vector<Point>& hull)
{
    if (hull.size() < 2)
        return false;
    else if (hull.size() == 2)
        return CCW(hull.front(), p, hull.back()) == 0;

    hull.push_back(hull[0]);
    bool result = true;

    for (int i = 0; i < (int)hull.size() - 1 && result; ++i)
        if (CCW(hull[i], hull[i + 1], p) < 0)
            result = false;

    hull.pop_back();
    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        std::vector<Point> black, white, bHull, wHull;
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            black.emplace_back(x, y);
        }

        for (int i = 0; i < m; ++i)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            white.emplace_back(x, y);
        }

        GetConvexHull(black, bHull);
        GetConvexHull(white, wHull);

        bool yes = true;
        for (int i = 0; i < (int)bHull.size() && yes; ++i)
            if (IsInside(bHull[i], wHull))
                yes = false;
        for (int i = 0; i < (int)wHull.size() && yes; ++i)
            if (IsInside(wHull[i], bHull))
                yes = false;

        printf("%s\n", yes ? "YES" : "NO");
    }

    return 0;
}