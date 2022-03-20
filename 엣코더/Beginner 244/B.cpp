#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    char comm[n+1];
    scanf("%s", comm);

    int x = 0, y = 0, dir = 0;
    const int dx[] = { 1, 0, -1, 0 };
    const int dy[] = { 0, -1, 0, 1 };
    for (int i = 0; i < n; ++i) {
        if (comm[i] == 'S') {
            x += dx[dir];
            y += dy[dir];
        } else {
            dir = (dir+1) % 4;
        }
    }
    printf("%d %d", x, y);

    return 0;
}