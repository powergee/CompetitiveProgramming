#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    int xMin = 10000, xMax = -10000, yMin = 10000, yMax = -10000;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        xMin = std::min(xMin, x);
        xMax = std::max(xMax, x);
        yMin = std::min(yMin, y);
        yMax = std::max(yMax, y);
    }

    printf("%d", (xMax-xMin) * (yMax-yMin));

    return 0;
}