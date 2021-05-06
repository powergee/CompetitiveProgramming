#include <iostream>
#include <queue>
#include <algorithm>

typedef long long Long;

struct State {
    int row, col;
    Long dist;

    State(int r, int c, Long d) {
        row = r;
        col = c;
        dist = d;
    }
};

const std::pair<int, int> DIRS[] { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int n, m;
Long w;
int map[2000][2000];
Long srcDist[2000][2000];
Long dstDist[2000][2000];

void fillDist(int row, int col, Long dist[][2000]) {
    std::fill(&dist[0][0], &dist[0][0] + 2000*2000, __INT64_MAX__);
    std::queue<State> q;
    q.emplace(row, col, 0);

    while (!q.empty()) {
        auto now = q.front();
        q.pop();

        if (dist[now.row][now.col] != __INT64_MAX__) {
            continue;
        }
        dist[now.row][now.col] = now.dist;

        for (int i = 0; i < 4; ++i) {
            int nr = now.row+DIRS[i].first;
            int nc = now.col+DIRS[i].second;
            if (0 <= nr && nr < n && 0 <= nc && nc < m && dist[nr][nc] == __INT64_MAX__ && map[nr][nc] != -1) {
                q.emplace(nr, nc, now.dist+w);
            }
        }
    }
}

int main() {
    scanf("%d %d %lld", &n, &m, &w);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            scanf("%d", &map[r][c]);
        }
    }

    fillDist(0, 0, srcDist);
    fillDist(n-1, m-1, dstDist);

    Long srcPortal = __INT64_MAX__/2;
    Long dstPortal = __INT64_MAX__/2;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (map[r][c] > 0) {
                if (srcDist[r][c] != __INT64_MAX__) {
                    srcPortal = std::min(srcPortal, map[r][c] + srcDist[r][c]);
                }
                if (dstDist[r][c] != __INT64_MAX__) {
                    dstPortal = std::min(dstPortal, map[r][c] + dstDist[r][c]);
                }
            }
        }
    }

    Long answer = std::min(srcDist[n-1][m-1], srcPortal+dstPortal);
    if (answer > __INT64_MAX__/2) {
        printf("-1");
    } else {
        printf("%lld", answer);
    }

    return 0;
}