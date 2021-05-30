#include <iostream>

int map[300][300];
int temp[300][300];

void rotate(int r, int c, int width, int height) {
    if (width < 2 || height < 2) {
        return;
    }

    for (int i = 0; i < width-1; ++i) {
        map[r][c+i] = temp[r][c+i+1];
    }

    for (int i = 0; i < height-1; ++i) {
        map[r+i][c+width-1] = temp[r+i+1][c+width-1];
    }

    for (int i = width-1; i > 0; --i) {
        map[r+height-1][c+i] = temp[r+height-1][c+i-1];
    }

    for (int i = height-1; i > 0; --i) {
        map[r+i][c] = temp[r+i-1][c];
    }

    rotate(r+1, c+1, width-2, height-2);
}

int main() {
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    while (r--) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                temp[i][j] = map[i][j];
            } 
        }

        rotate(0, 0, m, n);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}