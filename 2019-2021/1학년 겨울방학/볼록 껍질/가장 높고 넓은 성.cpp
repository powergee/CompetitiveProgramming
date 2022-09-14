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
    anglePivot = points[0];
    std::sort(points.begin(), points.end(), CompareByAngle);

    result.push_back(points[0]);
    result.push_back(points[1]);

    for (int i = 2; i < points.size(); ++i)
        TryToPush(points[i], result, points);
    TryToPush(points[0], result, points);
    result.pop_back();
}

Long CalcArea(int start, std::vector<Point>& hull)
{
    if (start > (int)hull.size() - 3)
        return 0;
    else
        return abs(CCW(hull[start], hull[start + 1], hull.back())) + CalcArea(start + 1, hull);
}

int main()
{
    int n;
    scanf("%d", &n);

    std::vector<Point> points;
    std::vector<int> used(n, 0);

    for (int i = 0; i < n; ++i)
    {
        Long x, y;
        scanf("%lld %lld", &x, &y);
        points.emplace_back(x, y, i);
    }

    std::sort(points.begin(), points.end(), CompareByAxis);

    for (int floor = 1; ; ++floor)
    {
        std::vector<Point> selected;

        for (int i = 0; i < n; ++i)
            if (used[points[i].Index] == 0)
                selected.push_back(points[i]);

        if (selected.size() < 3)
            break;

        std::vector<Point> hull;
        GetConvexHull(selected, hull);

        if (CalcArea(0, hull) == 0)
            break;

        for (Point& p : hull)
            used[p.Index] = floor;
    }

    for (int floor : used)
        printf("%d ", floor);

    return 0;
}