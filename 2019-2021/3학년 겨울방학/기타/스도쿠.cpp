#include <iostream>
#include <vector>

int board[9][10];
bool rowExist[9][10];
bool colExist[9][10];
bool subExist[3][3][10];

bool fillBoard(int r, int c) {
    if (r >= 9) {
        return true;
    } else if (board[r][c]) {
        return fillBoard(r+(c+1)/9, (c+1)%9);
    }

    for (int v = 1; v <= 9; ++v) {
        if (!rowExist[r][v] && !colExist[c][v] && !subExist[r/3][c/3][v]) {
            rowExist[r][v] = colExist[c][v] = subExist[r/3][c/3][v] = true;
            board[r][c] = v;
            if (fillBoard(r+(c+1)/9, (c+1)%9)) {
                return true;
            }
            rowExist[r][v] = colExist[c][v] = subExist[r/3][c/3][v] = false;
            board[r][c] = 0;
        }
    }
    return false;
}

int main() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            scanf("%d", &board[i][j]);
            rowExist[i][board[i][j]] = true;
            colExist[j][board[i][j]] = true;
            subExist[i/3][j/3][board[i][j]] = true;
        }
    }

    fillBoard(0, 0);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}