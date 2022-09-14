#include <iostream>
#include <vector>
#include <string>
#include <functional>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    std::vector<std::vector<int>> represent(n, std::vector<int>(m, -1));
    std::function<int(int, int, int)> findCycle = [&](int r, int c, int curr) -> int {
        if (represent[r][c] == curr) {
            return 1;
        } else if (represent[r][c] != -1) {
            return 0;
        }
        represent[r][c] = curr;

        if (map[r][c] == 'U') {
            return findCycle(r-1, c, curr);
        } else if (map[r][c] == 'D') {
            return findCycle(r+1, c, curr);
        } else if (map[r][c] == 'L') {
            return findCycle(r, c-1, curr);
        } else {
            return findCycle(r, c+1, curr);
        }
    };

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            answer += findCycle(i, j, i*m+j);
        }
    }
    printf("%d", answer);

    return 0;
}