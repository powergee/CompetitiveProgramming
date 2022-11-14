#include <iostream>

const int MAX = 1001;
int count[MAX][MAX];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        count[x1][y1]++;
        count[x1][y2]--;
        count[x2][y1]--;
        count[x2][y2]++;
    }

    for (int i = 0; i < MAX; ++i) {
        for (int j = 1; j < MAX; ++j) {
            count[i][j] += count[i][j-1];
        }
    }
    for (int j = 0; j < MAX; ++j) {
        for (int i = 1; i < MAX; ++i) {
            count[i][j] += count[i-1][j];
        }
    }

    int answer = 0;
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            if (count[i][j] == k) {
                ++answer;
            }
        }
    }
    std::cout << answer;

    return 0;
}