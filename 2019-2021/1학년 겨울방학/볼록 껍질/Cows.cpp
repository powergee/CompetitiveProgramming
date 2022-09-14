#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;
typedef std::pair<Long, Long> Point;

std::vector<Point> points, hull;
Point anglePivot = { -1, -1 };
int n;

Long Dist(const Point& p1, const Point& p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

Long CCW(const Point& p1, const Point& p2, const Point& p3)
{
    return p1.first * p2.second + p2.first * p3.second + p3.first * p1.second
        - p1.second * p2.first - p2.second * p3.first - p3.second * p1.first;
}

void TryToPush(const Point& p)
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

bool Compare(const Point& p1, const Point& p2)
{
    Long ccw = CCW(anglePivot, p1, p2);
    if (ccw > 0)
        return true;
    else if (ccw == 0)
        return Dist(anglePivot, p1) < Dist(anglePivot, p2);
    else return false;
}

Long CalcArea(int start)
{
    if (start > hull.size() - 3)
        return 0;

    return abs(CCW(hull[start], hull[start + 1], hull.back())) + CalcArea(start + 1);
}

int main()
{
    scanf("%d", &n);

    int first = 0;
    for (int i = 0; i < n; ++i)
    {
        Long x, y;
        scanf("%lld %lld", &x, &y);
        points.emplace_back(x, y);

        if (points[first] > points.back())
            first = points.size() - 1;
    }

    if (first != 0)
        std::swap(points[first], points[0]);

    anglePivot = points[0];
    std::sort(points.begin() + 1, points.end(), Compare);

    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (int i = 2; i < n; ++i)
        TryToPush(points[i]);
    TryToPush(points[0]);
    hull.pop_back();

    printf("%lld", CalcArea(0) / 100);

    return 0;
}