#include <iostream>
#include <algorithm>
#include <cstring>

int n, m, k, wLength;
char map[100][101];
char word[81];
int dp[100][100][80];

int countPath(int r, int c, int wStart) {
    int& result = dp[r][c][wStart];
    if (result != -1) {
        return result;
    }

    if (map[r][c] != word[wStart]) {
        return result = 0;
    }

    if (wStart == wLength-1) {
        return result = 1;
    }
    
    result = 0;
    for (int nr = std::max(r-k, 0); nr <= std::min(r+k, n-1); ++nr) {
        if (nr != r) {
            result += countPath(nr, c, wStart+1);
        }
    }
    for (int nc = std::max(c-k, 0); nc <= std::min(c+k, m-1); ++nc) {
        if (nc != c) {
            result += countPath(r, nc, wStart+1);
        }
    }

    return result;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%s", map[i]);
    }
    scanf("%s", word);
    wLength = strlen(word);
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(int), -1);
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            answer += countPath(i, j, 0);
        }
    }
    printf("%d", answer);
    
    return 0;
}