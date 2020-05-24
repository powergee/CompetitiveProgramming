#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> Point;

Point land[3];
int n;

int CCW(const Point& p1, const Point& p2, const Point& p3)
{
    int result = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second
        - p1.second * p2.first - p2.second * p3.first - p3.second * p1.first;
    
    if (result > 0)
        return 1;
    else if (result < 0)
        return -1;
    else return 0;
}

int main()
{
    for (int i = 0; i < 3; ++i)
        scanf("%d %d", &land[i].first, &land[i].second);

    if (CCW(land[0], land[1], land[2]) < 0)
        std::swap(land[1], land[2]);
    
    scanf("%d", &n);

    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        std::pair<int, int> tree;
        scanf("%d %d", &tree.first, &tree.second);

        if (CCW(land[0], land[1], tree) >= 0 && CCW(land[1], land[2], tree) >= 0 && CCW(land[2], land[0], tree) >= 0)
            ++count;
    }

    double area = abs(land[0].first * (land[1].second - land[2].second) + 
                    land[1].first * (land[2].second - land[0].second) + 
                    land[2].first * (land[0].second - land[1].second)) / 2.0;

    printf("%.1lf\n%d", area, count);

    return 0;
}