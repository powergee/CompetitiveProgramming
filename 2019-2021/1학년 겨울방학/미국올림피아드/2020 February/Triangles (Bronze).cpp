#include <iostream>
#include <vector>
#include <algorithm>

struct Point
{
    int X, Y;

    Point(int x, int y) : X(x), Y(y) {}

    Point operator-(const Point& p)
    {
        return { X - p.X, Y - p.Y };
    }
};

std::vector<Point> points;

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        points.emplace_back(x, y);
    }

    int area = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {
                Point& p1 = points[i], p2 = points[j], p3 = points[k];
                Point v[3]{ p1 - p2, p2 - p3, p3 - p1 };
                int count = 0;
                for (int i = 0; i < 3; ++i)
                    if (v[i].X == 0 || v[i].Y == 0)
                        ++count;

                if (count == 2)
                    area = std::max(area, abs((p1.X - p3.X) * (p2.Y - p1.Y) - (p1.X - p2.X) * (p3.Y - p1.Y)));
            }
        }
    }

    printf("%d", area);

    return 0;
}