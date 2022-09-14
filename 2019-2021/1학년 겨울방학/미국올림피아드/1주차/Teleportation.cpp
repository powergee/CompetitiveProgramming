#include <iostream>
#include <algorithm>

int main()
{
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);

    int dist[3];
    dist[0] = abs(a - b);
    dist[1] = abs(a - x) + abs(y - b);
    dist[2] = abs(a - y) + abs(x - b);

    printf("%d", *std::min_element(dist, dist + 3));

    return 0;
}