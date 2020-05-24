#include <iostream>

typedef std::pair<int, int> Point;
typedef std::pair<int, int> Range;

int GetCommonRange(const Range& r1, const Range& r2)
{
    if (r1.second < r2.first || r2.second < r1.first)
        return 0;
    else if (r1.first <= r2.first && r2.first <= r1.second && r1.second <= r2.second)
        return r1.second - r2.first;
    else if (r2.first <= r1.first && r1.first <= r2.second && r2.second <= r1.second)
        return r2.second - r1.first;
    else if (r2.first <= r1.first && r1.second <= r2.second)
        return r1.second - r1.first;
    else if (r1.first <= r2.first && r2.second <= r1.second)
        return r2.second - r2.first;

    return 0;
}

class Rect
{
public:
    Point leftBottom;
    Point rightTop;

    Rect(const Point left, const Point right) : leftBottom(left), rightTop(right) {}

    int GetIntersection(const Rect& r) const
    {
        int xLength = GetCommonRange(Range(leftBottom.first, rightTop.first), Range(r.leftBottom.first, r.rightTop.first));
        int yLength = GetCommonRange(Range(leftBottom.second, rightTop.second), Range(r.leftBottom.second, r.rightTop.second));

        return xLength * yLength;
    }

    int GetArea()
    {
        return (rightTop.first - leftBottom.first) * (rightTop.second - leftBottom.second);
    }
};

int main()
{
    int x1, y1, x2, y2;

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    Rect bill1({x1, y1}, {x2, y2});

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    Rect bill2({x1, y1}, {x2, y2});

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    Rect truck({x1, y1}, {x2, y2});

    printf("%d", bill1.GetArea() - bill1.GetIntersection(truck) + bill2.GetArea() - bill2.GetIntersection(truck));

    return 0;
}