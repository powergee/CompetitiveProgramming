#include <iostream>
#include <algorithm>
#define SIZE 1001

int map[SIZE][SIZE];
int answer[100];

int main() {
    std::fill(&map[0][0], &map[0][0] + sizeof(map) / sizeof(int), -1);
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int x, y, w, h;
        scanf("%d %d %d %d", &x, &y, &w, &h);
        for (int j = x; j < x+w; ++j) {
            for (int k = y; k < y+h; ++k) {
                map[j][k] = i;
            }
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            answer[map[i][j]]++;
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\n", answer[i]);
    }

    return 0;
}