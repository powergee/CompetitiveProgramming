#include <iostream>
#include <algorithm>
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

struct Shark {
    int row, col, speed, dir, size;
    Shark(int r, int c, int s, int d, int z) : row(r), col(c), speed(s), dir(d), size(z) {}

    void move(int rows, int cols) {
        static const int dr[] = { 0, -1, 1, 0, 0 };
        static const int dc[] = { 0, 0, 0, 1, -1 };

        row = dr[dir]*speed + row;
        col = dc[dir]*speed + col;

        while (row < 0 || row >= rows) {
            if (row < 0) {
                row = -row;
                dir = DOWN;
            } else {
                row = 2*rows-2-row;
                dir = UP;
            }
        }
        while (col < 0 || col >= cols) {
            if (col < 0) {
                col = -col;
                dir = RIGHT;
            } else {
                col = 2*cols-2-col;
                dir = LEFT;
            }
        }
    }
};

int main() {
    int r, c, m;
    scanf("%d %d %d", &r, &c, &m);

    Shark* map[r][c];
    Shark* next[r][c];
    std::fill(&map[0][0], &map[0][0] + sizeof(map) / sizeof(Shark*), (Shark*)0);

    for (int i = 0; i < m; ++i) {
        int r, c, s, d, z;
        scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
        --r, --c;
        map[r][c] = new Shark(r, c, s, d, z);
    }

    int catched = 0;
    for (int fisher = 0; fisher < c; ++fisher) {
        for (int i = 0; i < r; ++i) {
            if (map[i][fisher]) {
                catched += map[i][fisher]->size;
                map[i][fisher] = (Shark*)0;
                break;
            }
        }

        std::fill(&next[0][0], &next[0][0] + sizeof(next) / sizeof(Shark*), (Shark*)0);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (map[i][j]) {
                    map[i][j]->move(r, c);
                    int newR = map[i][j]->row;
                    int newC = map[i][j]->col;

                    if (next[newR][newC]) {
                        if (next[newR][newC]->size < map[i][j]->size) {
                            next[newR][newC] = map[i][j];
                        }
                    } else {
                        next[newR][newC] = map[i][j];
                    }
                }
            }
        }
        std::copy(&next[0][0], &next[0][0] + sizeof(next) / sizeof(Shark*), &map[0][0]);
    }

    printf("%d", catched);

    return 0;
}