#include <vector>
#include <algorithm>
#include <iostream>

bool map[301][301];
std::vector<int> connected[301];
bool visited[301];
int matching[301];

bool findValidPair(int start) {
    if (visited[start]) {
        return false;
    }
    visited[start] = true;

    for (int opposite : connected[start]) {
        if (matching[opposite] == 0 || findValidPair(matching[opposite])) {
            matching[opposite] = start;
            return true;
        }
    }
    return false;
}

int main() {
    int r, c, n;
    scanf("%d %d %d", &r, &c, &n);

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        map[a][b] = true;
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (!map[i][j]) {
                connected[i].push_back(j);
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= r; ++i) {
        std::fill(visited, visited+301, false);
        result += (findValidPair(i) ? 1 : 0);
    }

    printf("%d", result);

    return 0;
}