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

Long CCW(const Point& v1, const Point& v2)
{
    return v1.X * v2.Y - v2.X * v1.Y;
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

std::pair<Point, Point> GetFarthest(std::vector<Point>& hull)
{
    int p1 = 0, p2 = 1;
    double dist = (hull[p1] - hull[p2]).GetAbs();
    std::pair<Point, Point> result = {hull[p1], hull[p2]};

    for (int i = 0; i < (int)hull.size()*2; ++i)
    {
        int currP1 = (p1+1) % (int)hull.size();
        int currP2 = (p2+1) % (int)hull.size();
        double relCCW = CCW(hull[currP1] - hull[p1], hull[p2] - hull[currP2]);

        if (relCCW > 0)
            p1 = currP1;
        else if (relCCW < 0)
            p2 = currP2;
        else
        {
            p1 = currP1;
            p2 = currP2;
        }

        double currDist = (hull[p1] - hull[p2]).GetAbs();
        if (dist < currDist)
        {
            dist = currDist;
            result = {hull[p1], hull[p2]};
        }
    }

    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        std::vector<Point> points, hull;

        for (int i = 0; i < n; ++i)
        {
            Long x, y;
            scanf("%lld %lld", &x, &y);
            points.emplace_back(x, y);
        }
        std::sort(points.begin(), points.end(), CompareByAxis);
        GetConvexHull(points, hull);
        std::pair<Point, Point> result = GetFarthest(hull);

        printf("%lld %lld %lld %lld\n", result.first.X, result.first.Y, result.second.X, result.second.Y);
    }
}