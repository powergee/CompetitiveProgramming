#include <iostream>

typedef std::pair<int, int> Point;
typedef std::pair<Point, int> System;

int Dist(Point& p1, Point& p2)
{
    return ((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

bool Contains(System& sys, Point& p)
{
    return Dist(sys.first, p) < sys.second * sys.second;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        Point p1, p2;
        scanf("%d%d%d%d", &p1.first, &p1.second, &p2.first, &p2.second);
        int n;
        scanf("%d", &n);

        int count = 0;
        for (int i = 0; i < n; ++i)
        {
            System s;
            scanf("%d%d%d", &s.first.first, &s.first.second, &s.second);
            if (Contains(s, p1) ^ Contains(s, p2))
                ++count;
        }

        printf("%d\n", count);
    }

    return 0;
}