#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long Long;

struct Point
{
    Long X, Y;
    int Index;

    Point(Long x, Long y, int index) : X(x), Y(y), Index(index) {}
    Point(Long x, Long y) : Point(x, y, -1) {}

    Point operator-(Point& p) const
    {
        return {X-p.X, Y-p.Y, -1};
    }

    double GetAbs()
    {
        return sqrt(X*X + Y*Y);
    }

    Long operator*(Point& p) const
    {
        return X*p.X + Y*p.Y;
    }
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

    if (result.size() == 1 && !(result[0].X == points.back().X && result[0].Y == points.back().Y))
        result.push_back(points.back());
}

int main()
{
    int n, r;
    scanf("%d %d", &n, &r);
    std::vector<Point> points, hull;

    for (int i = 0; i < n; ++i)
    {
        Long x, y;
        scanf("%lld %lld", &x, &y);
        points.emplace_back(x, y);
    }
    std::sort(points.begin(), points.end(), CompareByAxis);
    GetConvexHull(points, hull);
    
    double answer = 0;
    int count = hull.size();

    for (int i = 0; i < count; ++i)
    {
        Point v1 = hull[i] - hull[(i+1) % count];
        Point v2 = hull[(i+2) % count] - hull[(i+1) % count];
        answer += r * (M_PI - acos(v1*v2 / (v1.GetAbs()*v2.GetAbs()))) + v1.GetAbs();
    }

    printf("%.12lf", answer);

    return 0;
}