#include <iostream>
#include <algorithm>

typedef long long Long;

Long height, width, cost;
Long map[1000][1000];
Long minUp[1000][1000];
Long minDown[1000][1000];
Long minLeft[1000][1000];
Long minRight[1000][1000];

Long getMinUp(int r, int c) {
    if (r == 1) {
        return map[r-1][c]+cost;
    }
    if (minUp[r][c] != 0) {
        return minUp[r][c];
    }

    return minUp[r][c] = std::min(map[r-1][c]+cost, getMinUp(r-1, c)+cost);
}

Long getMinDown(int r, int c) {
    if (r == height-2) {
        return map[r+1][c]+cost;
    }
    if (minDown[r][c] != 0) {
        return minDown[r][c];
    }

    return minDown[r][c] = std::min(map[r+1][c]+cost, getMinDown(r+1, c)+cost);
}

Long getMinLeft(int r, int c) {
    if (c == 1) {
        return map[r][c-1]+cost;
    }
    if (minLeft[r][c] != 0) {
        return minLeft[r][c];
    }

    return minLeft[r][c] = std::min(map[r][c-1]+cost, getMinLeft(r, c-1)+cost);
}

Long getMinRight(int r, int c) {
    if (c == width-2) {
        return map[r][c+1]+cost;
    }
    if (minRight[r][c] != 0) {
        return minRight[r][c];
    }

    return minRight[r][c] = std::min(map[r][c+1]+cost, getMinRight(r, c+1)+cost);
}

int main() {
    scanf("%lld %lld %lld", &height, &width, &cost);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            scanf("%lld", &map[i][j]);
        }
    }

    Long answer = __INT64_MAX__;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j > 0) {
                answer = std::min(answer, getMinLeft(i, j)+map[i][j]);
            }
            if (j < width-1) {
                answer = std::min(answer, getMinRight(i, j)+map[i][j]);
            }
            if (i > 0) {
                answer = std::min(answer, getMinUp(i, j)+map[i][j]);
            }
            if (i < height-1) {
                answer = std::min(answer, getMinDown(i, j)+map[i][j]);
            }

            if (i < height-1 && j < width-1) {
                answer = std::min(answer, getMinDown(i, j)+getMinRight(i, j));
            }
            if (i > 0 && j > 0) {
                answer = std::min(answer, getMinUp(i, j)+getMinLeft(i, j));
            }
            if (i > 0 && j < width-1) {
                answer = std::min(answer, getMinUp(i, j)+getMinRight(i, j));
            }
            if (i < height-1 && j > 0) {
                answer = std::min(answer, getMinDown(i, j)+getMinLeft(i, j));
            }
        }
    }

    printf("%lld", answer);

    return 0;
}