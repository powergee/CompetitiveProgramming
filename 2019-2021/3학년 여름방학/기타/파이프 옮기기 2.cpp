#include <iostream>
#include <algorithm>

typedef long long Long;
enum PipeKind { Horizontal = 0, Vertical = 1, Diagonal = 2 };

int n;
int map[32][32];
Long dp[3][32][32];

std::pair<int, int> getEndpoint(PipeKind kind, int row, int col) {
    switch (kind)
    {
    case Horizontal:
        return { row, col+1 };
    case Vertical:
        return { row+1, col };
    default:
        return { row+1, col+1 };
    }
}

bool isInMap(int row, int col) {
    return 0 <= row && row < n && 0 <= col && col < n;
}

bool isValid(PipeKind kind, int row, int col) {
    auto end = getEndpoint(kind, row, col);
    for (int r = row; r <= end.first; ++r) {
        for (int c = col; c <= end.second; ++c) {
            if (!isInMap(r, c) || map[r][c] == 1) {
                return false;
            }
        }
    }
    return true;
}

Long countCases(PipeKind kind, int row, int col) {
    if (!isValid(kind, row, col)) {
        return 0;
    }

    auto end = getEndpoint(kind, row, col);
    if (end.first == n-1 && end.second == n-1) {
        return 1;
    }

    Long& result = dp[kind][row][col];
    if (result != -1) {
        return result;
    }

    result = countCases(Diagonal, end.first, end.second);
    if (kind != Vertical) {
        result += countCases(Horizontal, end.first, end.second);
    }
    if (kind != Horizontal) {
        result += countCases(Vertical, end.first, end.second);
    }
    
    return result;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Long), -1LL);
    printf("%lld", countCases(Horizontal, 0, 0));

    return 0;
}