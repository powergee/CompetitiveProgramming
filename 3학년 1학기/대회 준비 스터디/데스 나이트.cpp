#include <iostream>
#include <queue>

struct State {
    int row, col;
    int count;

    State(int r, int c, int count) {
        row = r;
        col = c;
        this->count = count;
    }
};

bool visited[200][200];
const std::pair<int, int> MOVES[6] = { {-2, -1}, {-2, +1}, {0, -2}, {0, +2}, {+2, -1}, {+2, +1} };

int main() {
    int n, r1, c1, r2, c2;
    scanf("%d", &n);
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

    std::queue<State> q;
    q.emplace(r1, c1, 0);
    
    while (!q.empty()) {
        auto now = q.front();
        q.pop();

        if (visited[now.row][now.col]) {
            continue;
        }
        visited[now.row][now.col] = true;

        if (now.row == r2 && now.col == c2) {
            printf("%d", now.count);
            return 0;
        }

        for (int i = 0; i < 6; ++i) {
            int nr = now.row + MOVES[i].first;
            int nc = now.col + MOVES[i].second;

            if (0 <= nr && nr < n && 0 <= nc && nc < n && !visited[nr][nc]) {
                q.emplace(nr, nc, now.count+1);
            }
        }
    }

    printf("-1");

    return 0;
}