#include <iostream>
#include <queue>

struct State {
    int r, c;
    State(int r, int c) {
        this->r = r;
        this->c = c;
    }
};

int n, m, d;
std::string map[500];
int dist[500][500];

bool isValid(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    d = 2;

    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
        std::fill(dist[i], dist[i]+m, __INT32_MAX__/2);
    }

    std::deque<State> q;
    q.emplace_back(0, 0);
    dist[0][0] = 0;
    
    while (!q.empty()) {
        auto now = q.front();
        q.pop_front();

        // 그냥 이동 (거리 0)
        for (int i = 0; i < 4; ++i) {
            static const int dr[4] = { 0, 0, 1, -1 };
            static const int dc[4] = { 1, -1, 0, 0 };
            int nr = now.r+dr[i];
            int nc = now.c+dc[i];
            if (!isValid(nr, nc) || map[nr][nc] == '#') {
                continue;
            }
            if (dist[now.r][now.c] < dist[nr][nc]) {
                dist[nr][nc] = dist[now.r][now.c];
                q.emplace_front(nr, nc);
            }
        }

        // 부수고 이동 (거리 1)
        if (now.r-d+1 <= n-1 && n-1 <= now.r+d-1 && now.c-d+1 <= m-1 && m-1 <= now.c+d-1) {
            int nr = n-1;
            int nc = m-1;
            if (dist[now.r][now.c]+1 < dist[nr][nc]) {
                dist[nr][nc] = dist[now.r][now.c]+1;
                q.emplace_back(nr, nc);
            }
        }
        for (int dc = -d+1; dc < d; ++dc) {
            int nr = std::max(0, now.r-d);
            int nc = now.c+dc;
            if (!isValid(nr, nc)) {
                continue;
            }
            if (dist[now.r][now.c]+1 < dist[nr][nc]) {
                dist[nr][nc] = dist[now.r][now.c]+1;
                q.emplace_back(nr, nc);
            }
        }
        for (int dc = -d+1; dc < d; ++dc) {
            int nr = std::min(n-1, now.r+d);
            int nc = now.c+dc;
            if (!isValid(nr, nc)) {
                continue;
            }
            if (dist[now.r][now.c]+1 < dist[nr][nc]) {
                dist[nr][nc] = dist[now.r][now.c]+1;
                q.emplace_back(nr, nc);
            }
        }
        for (int dr = -d+1; dr < d; ++dr) {
            int nc = std::max(0, now.c-d);
            int nr = now.r+dr;
            if (!isValid(nr, nc)) {
                continue;
            }
            if (dist[now.r][now.c]+1 < dist[nr][nc]) {
                dist[nr][nc] = dist[now.r][now.c]+1;
                q.emplace_back(nr, nc);
            }
        }
        for (int dr = -d+1; dr < d; ++dr) {
            int nc = std::min(m-1, now.c+d);
            int nr = now.r+dr;
            if (!isValid(nr, nc)) {
                continue;
            }
            if (dist[now.r][now.c]+1 < dist[nr][nc]) {
                dist[nr][nc] = dist[now.r][now.c]+1;
                q.emplace_back(nr, nc);
            }
        }
    }

    printf("%d", dist[n-1][m-1]);

    return 0;
}