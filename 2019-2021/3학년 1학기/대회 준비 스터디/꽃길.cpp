#include <iostream>
#include <algorithm>

int n;
int map[10][10];
bool used[10][10];

bool isValid(int r, int c) {
    return 0 < r && r < n-1 && 0 < c && c < n-1;
}

bool canPlant(int r, int c) {
    return isValid(r, c) && !used[r][c] && !used[r-1][c] && !used[r][c-1] && !used[r+1][c] && !used[r][c+1]; 
}

int getCost(int r, int c) {
    return map[r][c] + map[r-1][c] + map[r][c-1] + map[r+1][c] + map[r][c+1];
}

int getMinCost(int start, int remain) {
    if (remain == 0) {
        return 0;
    }

    if (n*n <= start) {
        return __INT32_MAX__/2;
    }

    int answer = __INT32_MAX__;
    int r = start / n;
    int c = start % n;

    if (canPlant(r, c)) {
        used[r][c] = used[r-1][c] = used[r][c-1] = used[r+1][c] = used[r][c+1] = true;
        answer = std::min(answer, getCost(r, c) + getMinCost(start+1, remain-1));
        used[r][c] = used[r-1][c] = used[r][c-1] = used[r+1][c] = used[r][c+1] = false;
    }
    answer = std::min(answer, getMinCost(start+1, remain));

    return answer;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    printf("%d", getMinCost(0, 3));

    return 0;
}