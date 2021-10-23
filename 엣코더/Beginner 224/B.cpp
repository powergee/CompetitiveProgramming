#include <iostream>

int main() {
    int h, w;
    scanf("%d %d", &h, &w);
    int map[h][w];

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    bool yes = true;
    for (int i1 = 0; i1 < h; ++i1) {
        for (int i2 = i1+1; i2 < h; ++i2) {
            for (int j1 = 0; j1 < w; ++j1) {
                for (int j2 = j1+1; j2 < w; ++j2) {
                    if (map[i1][j1] + map[i2][j2] > map[i2][j1] + map[i1][j2]) {
                        yes = false;
                    }
                }
            }
        }
    }

    printf(yes ? "Yes" : "No");

    return 0;
}