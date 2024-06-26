#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

struct LockedInfo {
    char ch;
    int r, c;
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int h, w;
        scanf("%d %d", &h, &w);

        auto isValid = [&](int r, int c) -> bool {
            return 0 <= r && r < h && 0 <= c && c < w;
        };

        char map[h][w+1];
        for (int i = 0; i < h; ++i) {
            scanf("%s", map[i]);
        }

        char keys[27];
        bool hasKey[26] = { };
        scanf("%s", keys);
        int keyLength = strlen(keys);
        for (int i = 0; i < keyLength; ++i) {
            if (islower(keys[i])) {
                hasKey[keys[i]-'a'] = true;
            }
        }

        std::queue<std::pair<int, int>> locked[26];
        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<bool>> visited(h);

        for (int i = 0; i < h; ++i) {
            visited[i].resize(w, false);
            for (int j = 0; j < w; ++j) {
                if ((i == 0 || j == 0 || i == h-1 || j == w-1) && map[i][j] != '*') {
                    if (map[i][j] == '.' || map[i][j] == '$' || islower(map[i][j]) || hasKey[map[i][j]-'A']) {
                        q.emplace(i, j);
                    } else {
                        locked[map[i][j]-'A'].emplace(i, j);
                    }
                }
            }
        }

        int answer = 0;
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            if (visited[curr.first][curr.second]) {
                continue;
            }
            visited[curr.first][curr.second] = true;

            if (map[curr.first][curr.second] == '$') {
                ++answer;
            } else if (islower(map[curr.first][curr.second])) {
                hasKey[map[curr.first][curr.second]-'a'] = true;
                while (!locked[map[curr.first][curr.second]-'a'].empty()) {
                    auto pos = locked[map[curr.first][curr.second]-'a'].front();
                    locked[map[curr.first][curr.second]-'a'].pop();
                    if (!visited[pos.first][pos.second]) {
                        q.emplace(pos.first, pos.second);
                    }
                }
            }

            const static int dr[] = { 0, 0, 1, -1 };
            const static int dc[] = { 1, -1, 0, 0 };
            for (int i = 0; i < 4; ++i) {
                int nr = curr.first + dr[i];
                int nc = curr.second + dc[i];
                
                if (!isValid(nr, nc) || visited[nr][nc] || map[nr][nc] == '*') {
                    continue;
                } else if (isupper(map[nr][nc])) {
                    if (hasKey[map[nr][nc]-'A']) {
                        q.emplace(nr, nc);
                    } else {
                        locked[map[nr][nc]-'A'].emplace(nr, nc);
                    }
                } else {
                    q.emplace(nr, nc);
                }
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}