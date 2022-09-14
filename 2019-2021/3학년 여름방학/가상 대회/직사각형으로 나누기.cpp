#include <iostream>
#include <algorithm>

typedef long long Long;

int n, m;
char mapStr[100][101];
int map[100][100];
Long leftTop[100][100];

Long sumFromLeftTop(int row, int col) {
    if (row < 0 || col < 0) {
        return 0;
    }
    if (row == 0 && col == 0) {
        return map[row][col];
    }

    Long& result = leftTop[row][col];
    if (result != -1) {
        return result;
    }

    result = sumFromLeftTop(row-1, col) + sumFromLeftTop(row, col-1) - sumFromLeftTop(row-1, col-1) + map[row][col];
    return result;
}

Long sumFromRightTop(int row, int col) {
    return sumFromLeftTop(row, m-1) - sumFromLeftTop(row, col-1);
}

Long sumFromLeftBottom(int row, int col) {
    return sumFromLeftTop(n-1, col) - sumFromLeftTop(row-1, col);
}

Long sumFromRightBottom(int row, int col) {
    return sumFromLeftBottom(row, m-1) - sumFromLeftBottom(row, col-1);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", mapStr[i]);
        for (int j = 0; j < m; ++j) {
            map[i][j] = mapStr[i][j] - '0';
        }
    }

    std::fill(&leftTop[0][0], &leftTop[0][0] + sizeof(leftTop) / sizeof(Long), -1);

    Long answer = -1;
    for (int i = 0; i < m-2; ++i) {
        for (int j = i+1; j < m-1; ++j) {
            Long s1 = sumFromLeftTop(n-1, i);
            Long s2 = sumFromLeftTop(n-1, j) - s1;
            Long s3 = sumFromLeftTop(n-1, m-1) - s1 - s2;
            answer = std::max(answer, s1*s2*s3);
        }
    }

    for (int i = 0; i < n-2; ++i) {
        for (int j = i+1; j < n-1; ++j) {
            Long s1 = sumFromLeftTop(i, m-1);
            Long s2 = sumFromLeftTop(j, m-1) - s1;
            Long s3 = sumFromLeftTop(n-1, m-1) - s1 - s2;
            answer = std::max(answer, s1*s2*s3);
        }
    }

    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < m-1; ++j) {
            answer = std::max(answer, sumFromLeftTop(i, j) * sumFromRightTop(i, j+1) * sumFromLeftBottom(i+1, m-1));
            answer = std::max(answer, sumFromLeftTop(i, m-1) * sumFromLeftBottom(i+1, j) * sumFromRightBottom(i+1, j+1));
            answer = std::max(answer, sumFromLeftTop(n-1, j) * sumFromRightTop(i, j+1) * sumFromRightBottom(i+1, j+1));
            answer = std::max(answer, sumFromLeftTop(i, j) * sumFromLeftBottom(i+1, j) * sumFromRightTop(n-1, j+1));
        }
    }

    printf("%lld", answer);

    return 0;
}