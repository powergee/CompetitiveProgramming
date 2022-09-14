#include <iostream>
#include <vector>

int main() {
    int w, h, k;
    scanf("%d %d %d", &w, &h, &k);

    std::vector<std::vector<int>> rectMap(h+3, std::vector<int>(w+3, 0));
    std::vector<std::vector<int>> diamMap(h+3, std::vector<int>(w+3, 0));

    for (int i = 0; i < k; ++i) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int px, py, qx, qy;
            scanf("%d %d %d %d", &px, &py, &qx, &qy);
            px++, py++, qx++, qy++;

            rectMap[py][px]++;
            rectMap[py][qx+1]--;

            rectMap[qy+1][px]--;
            rectMap[qy+1][qx+1]++;
        } else {
            int px, py, r;
            scanf("%d %d %d", &px, &py, &r);
            px++, py++;

            diamMap[py-r][px]++;
            diamMap[py+1][px+r+1]--;
            
            diamMap[py-r+1][px]++;
            diamMap[py+1][px+r]--;

            diamMap[py+1][px-r]--;
            diamMap[py+r+1][px]++;

            diamMap[py+1][px-r-1]--;
            diamMap[py+r+2][px]++;
        }
    }

    for (int r = 0; r < rectMap.size(); ++r) {
        for (int c = 1; c < rectMap[r].size(); ++c) {
            rectMap[r][c] += rectMap[r][c-1];
        }
    }
    for (int c = 0; c < rectMap[0].size(); ++c) {
        for (int r = 1; r < rectMap.size(); ++r) {
            rectMap[r][c] += rectMap[r-1][c];
        }
    }

    for (int r = 1; r < diamMap.size(); ++r) {
        for (int c = 1; c < diamMap[r].size(); ++c) {
            diamMap[r][c] += diamMap[r-1][c-1];
        }
    }
    for (int r = 1; r < diamMap.size(); ++r) {
        for (int c = int(diamMap[r].size())-2; c >= 0; --c) {
            diamMap[r][c] += diamMap[r-1][c+1];
        }
    }

    for (int r = 1; r <= h; ++r) {
        for (int c = 1; c <= w; ++c) {
            putchar((rectMap[r][c] + diamMap[r][c]) % 2 == 0 ? '.' : '#');
        }
        putchar('\n');
    }

    return 0;
}