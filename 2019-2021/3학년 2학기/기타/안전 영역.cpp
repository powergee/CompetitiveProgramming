#include <iostream>

int n;
int map[100][100];
bool visited[100][100];

void DFS(int r, int c, int water) {
    visited[r][c] = true;
    
    static const int dr[4] = { 0, 0, 1, -1 };
    static const int dc[4] = { 1, -1, 0, 0 };
    for (int i = 0; i < 4; ++i) {
        int nr = r+dr[i];
        int nc = c+dc[i];
        if (0 <= nr && nr < n && 0 <= nc && nc < n && !visited[nr][nc] && water < map[nr][nc]) {
            DFS(nr, nc, water);
        }
    }
}

int countSafeArea(int water) {
    for (int i = 0; i < n; ++i) {
        std::fill(visited[i], visited[i]+n, false);
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (water < map[i][j] && !visited[i][j]) {
                DFS(i, j, water);
                ++count;
            }
        }
    }
    
    return count;
}

int main() {
    scanf("%d", &n);

    int highest = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &map[i][j]);
            highest = std::max(highest, map[i][j]);
        }
    }

    int answer = 1;
    for (int w = 1; w <= highest; ++w) {
        answer = std::max(answer, countSafeArea(w));
    }

    printf("%d", answer);
    return 0;
}