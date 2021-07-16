#include <vector>
#include <algorithm>
#include <iostream>
#define LEFT_MAX 1001
#define RIGHT_MAX 1001

std::vector<int> connected[LEFT_MAX];
bool visited[LEFT_MAX];
int matching[RIGHT_MAX];

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
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        int count;
        scanf("%d", &count);
        while (count--) {
            int work;
            scanf("%d", &work);
            connected[i].push_back(work);
        }
    }

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        std::fill(visited, visited+n+1, false);
        result += (findValidPair(i) ? 1 : 0);
    }

    printf("%d", result);

    return 0;
}