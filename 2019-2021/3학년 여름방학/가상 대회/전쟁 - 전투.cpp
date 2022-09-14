#include <iostream>

int n, m;
char map[100][101];
bool visited[100][100];

bool isValid(int r, int c) {
    return 0 <= r && r < m &&
           0 <= c && c < n;
}

long long getSize(int r, int c) {
    if (visited[r][c]) {
        return 0;
    }
    visited[r][c] = true;

    static const int dr[4] = {0, 0, 1, -1};
    static const int dc[4] = {1, -1, 0, 0};
    long long size = 1;
    for (int i = 0; i < 4; ++i) {
        int nr = r+dr[i];
        int nc = c+dc[i];
        if (isValid(nr, nc) && map[nr][nc] == map[r][c]) {
            size += getSize(nr, nc);
        }
    }

    return size;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        scanf("%s", map[i]);
    }

    long long p = 0, q = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            long long size = getSize(i, j);
            if (map[i][j] == 'W') {
                p += size*size;
            } else {
                q += size*size;
            }
        }
    }

    printf("%lld %lld", p, q);

    return 0;
}