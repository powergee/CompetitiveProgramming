#include <iostream>
#include <vector>
#include <algorithm>
#define LEFT_MAX 3280
#define RIGHT_MAX 3280

char map[80][81];
int rows, cols;
std::vector<int> connected[LEFT_MAX];
bool visited[LEFT_MAX];
int matching[RIGHT_MAX];

bool findValidPair(int start) {
    if (visited[start]) {
        return false;
    }
    visited[start] = true;

    for (int opposite : connected[start]) {
        if (matching[opposite] == -1 || findValidPair(matching[opposite])) {
            matching[opposite] = start;
            return true;
        }
    }
    return false;
}

int toIndex(int r, int c) {
    return r + rows*(c/2);
}

bool isValid(int r, int c) {
    return 0 <= r && r < rows && 0 <= c && c < cols && map[r][c] != 'x';
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &rows, &cols);

        int leftMax = rows * ((cols+1)/2);
        int rightMax = rows * (cols/2);
        for (int i = 0; i < leftMax; ++i) {
            connected[i].clear();
        }
        std::fill(visited, visited+leftMax, false);
        std::fill(matching, matching+rightMax, -1);

        int blankCount = 0;
        for (int i = 0; i < rows; ++i) {
            scanf("%s", map[i]);
            for (int j = 0; j < cols; ++j) {
                if (map[i][j] == '.') {
                    ++blankCount;
                }
            }
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; j += 2) {
                if (map[i][j] == 'x') {
                    continue;
                }
                
                int idx = toIndex(i, j);
                if (isValid(i, j-1)) {
                    connected[idx].push_back(toIndex(i, j-1));
                }
                if (isValid(i, j+1)) {
                    connected[idx].push_back(toIndex(i, j+1));
                }
                if (isValid(i-1, j-1)) {
                    connected[idx].push_back(toIndex(i-1, j-1));
                }
                if (isValid(i-1, j+1)) {
                    connected[idx].push_back(toIndex(i-1, j+1));
                }
                if (isValid(i+1, j-1)) {
                    connected[idx].push_back(toIndex(i+1, j-1));
                }
                if (isValid(i+1, j+1)) {
                    connected[idx].push_back(toIndex(i+1, j+1));
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < leftMax; ++i) {
            std::fill(visited, visited+leftMax, false);
            result += (findValidPair(i) ? 1 : 0);
        }

        printf("%d\n", blankCount - result);
    }
}