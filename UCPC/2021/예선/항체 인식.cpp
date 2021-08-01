#include <iostream>
#include <queue>

int n, m;
int before[30][30];
int after[30][30];
bool diff[30][30];
bool visited[30][30];
std::pair<int, int> diffPos = {-1, -1};

bool isValid(std::pair<int, int>& pos) {
    return 0 <= pos.first && pos.first < n &&
           0 <= pos.second && pos.second < m;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &before[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &after[i][j]);
            diff[i][j] = before[i][j] != after[i][j];
            if (diff[i][j]) {
                diffPos = {i, j};
            }
        }
    }

    if (diffPos.first == -1) {
        printf("YES");
    } else {
        std::queue<std::pair<int, int>> q;
        q.push(diffPos);
        visited[diffPos.first][diffPos.second] = true;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            static const int dr[] = { 0, 0, 1, -1 };
            static const int dc[] = { 1, -1, 0, 0 };
            for (int i = 0; i < 4; ++i) {
                std::pair<int, int> next = { curr.first+dr[i], curr.second+dc[i] };
                if (isValid(next) && !visited[next.first][next.second] &&
                    before[curr.first][curr.second] == before[next.first][next.second]) {
                    visited[next.first][next.second] = true;
                    q.push(next);
                }
            }
        }

        bool allSame = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (diff[i][j] != visited[i][j]) {
                    allSame = false;
                } else if (visited[i][j] && after[diffPos.first][diffPos.second] != after[i][j]) {
                    allSame = false;
                }
            }
        }
        printf(allSame ? "YES" : "NO");
    }

    return 0;
}