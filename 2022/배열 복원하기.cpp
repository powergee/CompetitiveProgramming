#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int h, w, x, y;
    std::cin >> h >> w >> x >> y;

    int map[h+x][w+y];
    for (int i = 0; i < h+x; ++i) {
        for (int j = 0; j < w+y; ++j) {
            std::cin >> map[i][j];
        }
    }

    int origin[h+x][w+y];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (x <= i && y <= j) {
                origin[i][j] = map[i][j] - origin[i-x][j-y];
            } else {
                origin[i][j] = map[i][j];
            }
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            std::cout << origin[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}