#include <iostream>
#include <algorithm>

int n;
int map[100][100];
bool visited[100][100];

const int dr[] = { 0, 1, 0, -1 };
const int dc[] = { 1, 0, -1, 0 };

bool findPath(int allowedMin, int allowedMax, int row, int col) {
    if (row == n-1 && col == n-1) {
        return true;
    }

    visited[row][col] = true;

    for (int i = 0; i < 4; ++i) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if (0 <= nr && nr < n && 0 <= nc && nc < n && !visited[nr][nc] && allowedMin <= map[nr][nc] && map[nr][nc] <= allowedMax) {
            if (findPath(allowedMin, allowedMax, nr, nc)) {
                return true;
            }
        }
    }

    return false;
}

bool isPossible(int diff) {
    int init = map[0][0];
    for (int min = init-diff; min <= init; ++min) {
        std::fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(bool), false);
        if (findPath(min, min+diff, 0, 0)) {
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    int left = 0, right = 200;
    while (left < right) {
        int mid = (left+right) / 2;
        if (isPossible(mid)) {
            right = mid;
        } else {
            left = mid+1;
        }
    }
    printf("%d", left);

    return 0;
}