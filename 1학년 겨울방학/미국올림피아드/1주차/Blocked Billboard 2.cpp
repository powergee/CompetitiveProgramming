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

    bool IsCovering(const Rect& r)
    {
        return  (leftBottom.second <= r.leftBottom.second && r.rightTop.second <= rightTop.second && !(r.leftBottom.first <= leftBottom.first && rightTop.first <= r.rightTop.first)) ||
                (leftBottom.first <= r.leftBottom.first && r.rightTop.first <= rightTop.first && !(r.leftBottom.second <= leftBottom.second && rightTop.second <= r.rightTop.second));
    }
};

int main()
{
    int x1, y1, x2, y2;

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    Rect lawn({x1, y1}, {x2, y2});

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    Rect feed({x1, y1}, {x2, y2});

    if (feed.IsCovering(lawn))
        printf("%d", lawn.GetArea() - lawn.GetIntersection(feed));
    else printf("%d", lawn.GetArea());

    return 0;
}