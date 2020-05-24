#include <iostream>
#include <algorithm>

std::pair<int, int> points[100000];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        points[i] = {x, y};
    }

    std::sort(points, points + n);
    for (int i = 0; i < n; ++i)
        printf("%d %d\n", points[i].first, points[i].second);

    return 0;
}