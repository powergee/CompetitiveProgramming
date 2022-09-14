#include <iostream>
#include <algorithm>
#define UND -2
#define INF -1
#define INSTACK -3

int n, m;
int dp[50][50], map[50][50];

int DR[] = { -1, 1, 0, 0 };
int DC[] = { 0, 0, -1, 1 };

bool isValid(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m && map[r][c] != UND;
}

int getMaxMovement(int r, int c) {
    if (map[r][c] == UND) {
        return 0;
    }

    int& result = dp[r][c];
    if (result == INSTACK) {
        return INF;
    } else if (result != UND) {
        return result;
    }

    result = INSTACK;
    int current = 1;
    for (int i = 0; i < 4; ++i) {
        int nr = DR[i]*map[r][c] + r;
        int nc = DC[i]*map[r][c] + c;
        if (isValid(nr, nc)) {
            int next = getMaxMovement(nr, nc);
            if (next == INF) {
                current = INF;
                break;
            } else {
                current = std::max(current, next+1);
            }
        }
    }

    return result = current;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        char line[51];
        scanf("%s", line);
        for (int j = 0; j < m; ++j) {
            map[i][j] = (line[j] == 'H' ? UND : line[j]-'0');
            dp[i][j] = UND;
        }
    }

    printf("%d", getMaxMovement(0, 0));

    return 0;
}