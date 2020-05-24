#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long Long;

struct Point
{
    Long X, Y;
    
    Point (Long x, Long y) : X(x), Y(y) {}

    Point operator-(const Point& p)
    {
        return Point(X - p.X, Y - p.Y);
    }

    Long operator*(const Point& p)
    {
        return X * p.X + Y * p.Y;
    }
};

Point anglePivot(-1, -1);

Long Dist(const Point& p)
{
    return p.X * p.X + p.Y * p.Y;
}

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

    for (int i = 2; i < (int)points.size(); ++i)
        TryToPush(points[i], result, points);
    TryToPush(points[0], result, points);
    result.pop_back();

    if ((int)result.size() == 1 && !(result[0].X == points.back().X && result[0].Y == points.back().Y))
        result.push_back(points.back());
}

double CalcWallSize(std::vector<Point>& hull, double r)
{
    double result = 0;
    hull.push_back(hull[0]);
    hull.push_back(hull[1]);

    for (int i = 0; i < (int)hull.size() - 2; ++i)
        result += sqrt(Dist(hull[i], hull[i + 1]));

    for (int i = 0; i < (int)hull.size() - 2; ++i)
    {
        Point v1 = hull[i + 1] - hull[i];
        Point v2 = hull[i + 2] - hull[i + 1];

        result += r * acos((double)(v1 * v2) / (sqrt(Dist(v1)) * sqrt(Dist(v2))));
    }

    hull.pop_back();
    hull.pop_back();

    return result;
}

int main()
{
    int n, l;
    scanf("%d %d", &n, &l);

    std::vector<Point> points, hull;
    for (int i = 0; i < n; ++i)
    {
        Long x, y;
        scanf("%lld %lld", &x, &y);
        points.emplace_back(x, y);
    }

    std::sort(points.begin(), points.end(), CompareByAxis);
    GetConvexHull(points, hull);
    printf("%lld", (Long)round(CalcWallSize(hull, l)));
}