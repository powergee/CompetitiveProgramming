#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

enum CellKind {
    Blank, Green, Red, Flower
};

struct CellInfo {
    CellKind kind;
    int appliedTime;
};

struct State {
    int r, c;
    int prevRow, prevCol;
    CellInfo cell;

    State(int r, int c, int prevRow, int prevCol, CellKind kind, int time) {
        this->r = r;
        this->c = c;
        this->prevRow = prevRow;
        this->prevCol = prevCol;
        cell = { kind, time };
    }
};

int n, m, g, r;
int map[50][50];
CellInfo applied[50][50];
std::vector<std::pair<int, int>> usable;
std::vector<CellKind> assigned;

bool isOpposite(CellKind k1, CellKind k2) {
    if ((k1 == Green || k1 == Red) && (k2 == Green || k2 == Red)) {
        return ((k1 == Green && k2 == Red) || (k1 == Red && k2 == Green));
    }
    return false;
}

int getMaxCount() {
    std::queue<State> q;
    for (int i = 0; i < assigned.size(); ++i) {
        if (assigned[i] != Blank) {
            q.emplace(usable[i].first, usable[i].second, -1, -1, assigned[i], 0);
        }
    }

    const CellInfo initInfo = { Blank, -1 };
    std::fill(&applied[0][0], &applied[0][0] + sizeof(applied) / sizeof(CellInfo), initInfo);

    int count = 0;
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        if (curr.prevRow != -1 && curr.prevCol != -1 &&
            applied[curr.prevRow][curr.prevCol].kind == Flower) {
            continue;
        }
        
        if (applied[curr.r][curr.c].kind == Blank) {
            applied[curr.r][curr.c] = curr.cell;

            const int dr[4] = { 0, 0, 1, -1 };
            const int dc[4] = { 1, -1, 0, 0 };
            for (int i = 0; i < 4; ++i) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];
                if (0 <= nr && nr < n && 0 <= nc && nc < m &&
                    applied[nr][nc].kind == Blank && map[nr][nc] != 0) {
                    q.emplace(nr, nc, curr.r, curr.c, curr.cell.kind, curr.cell.appliedTime+1);
                }
            }
        } else if (isOpposite(applied[curr.r][curr.c].kind, curr.cell.kind) && 
                   applied[curr.r][curr.c].appliedTime == curr.cell.appliedTime) {
            applied[curr.r][curr.c].kind = Flower;
            ++count;
        }
    }

    return count;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &g, &r);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
            if (map[i][j] == 2) {
                usable.emplace_back(i, j);
            }
        }
    }
    assigned.resize(usable.size(), Blank);
    std::fill(assigned.begin(), assigned.begin() + g, Green);
    std::fill(assigned.begin() + g, assigned.begin() + g + r, Red);
    std::sort(assigned.begin(), assigned.end());

    int answer = 0;
    do {
        answer = std::max(answer, getMaxCount());
    } while (std::next_permutation(assigned.begin(), assigned.end()));

    printf("%d", answer);

    return 0;
}