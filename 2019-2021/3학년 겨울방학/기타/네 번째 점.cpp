#include <iostream>

int main() {
    int cx = 0, cy = 0;
    for (int i = 0; i < 3; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        cx ^= x;
        cy ^= y;
    }
    printf("%d %d", cx, cy);
    return 0;
}