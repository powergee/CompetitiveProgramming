#include <iostream>
#include <algorithm>

char map[3*1024][3*1024*2];

void drawTriangles(int x, int y, int n) {
    if (n == 3) {
        for (int c = x; c < x + (2*n-1); ++c) {
            map[y+2][c] = '*';
            map[abs(c-x-2)+y][c] = '*';
        }
    } else {
        drawTriangles(x+n/2, y, n/2);
        drawTriangles(x, y+n/2, n/2);
        drawTriangles(x+n, y+n/2, n/2);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int r = 0; r < n; ++r) {
        std::fill(map[r], map[r] + (2*n - 1), ' ');
    }

    drawTriangles(0, 0, n);

    for (int r = 0; r < n; ++r) {
        printf("%s\n", map[r]);
    }
}