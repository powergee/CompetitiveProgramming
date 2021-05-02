#include <iostream>
#include <algorithm>

bool map[1001][1001];
int maxLeft[1001][1001];
int maxUp[1001][1001];
int maxSquare[1001][1001];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int r = 1; r <= n; ++r) {
        char str[1001];
        scanf("%s", str);
        for (int c = 1; c <= m; ++c) {
            map[r][c] = (str[c-1] == '1');
        }
    }

    int answer = 0;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            if (map[r][c]) {
                maxLeft[r][c] = maxLeft[r][c-1] + 1;
                maxUp[r][c] = maxUp[r-1][c] + 1;
                maxSquare[r][c] = std::min(maxSquare[r-1][c-1], std::min(maxLeft[r][c-1], maxUp[r-1][c])) + 1;

                answer = std::max(answer, maxSquare[r][c]*maxSquare[r][c]);
            } else {
                maxSquare[r][c] = maxLeft[r][c] = maxUp[r][c] = 0;
            }
        }
    }

    printf("%d", answer);
    return 0;
}