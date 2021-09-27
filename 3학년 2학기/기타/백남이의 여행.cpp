#include <iostream>

int n;
bool visited[500][500];
int count = 0;

bool isPossible(int row, int col) {
    visited[row][col] = true;
    ++count;

    if (count == n*n) {
        return true;
    }

    const static int dr[] { -1, -2, -2, -1, 1, 2, 2, 1 };
    const static int dc[] { 2, 1, -1, -2, -2, -1, 1, 2 };
    for (int i = 0; i < 8; ++i) {
        int nr = row+dr[i];
        int nc = col+dc[i];
        if (0 <= nr && nr < n && 0 <= nc && nc < n && !visited[nr][nc] && isPossible(nr, nc)) {
            return true;
        }
    }

    --count;
    visited[row][col] = false;
    return false;
}

int main() {
    scanf("%d", &n);
    printf(isPossible(0, 0) ? "Yes" : "No");
        
    return 0;
}