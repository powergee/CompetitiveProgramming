#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> map(n, std::vector<int>(m));
    std::vector<int> rowSum(n, 0), colSum(m, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> map[i][j];
            rowSum[i] += map[i][j];
            colSum[j] += map[i][j];
        }
    }

    int answer = INT32_MIN;
    for (int r1 = 0; r1 < n; ++r1) {
        for (int r2 = r1+1; r2 < n; ++r2) {
            for (int c1 = 0; c1 < m; ++c1) {
                for (int c2 = c1+1; c2 < m; ++c2) {
                    int curr = rowSum[r1] + rowSum[r2] + colSum[c1] + colSum[c2]
                                - map[r1][c1] - map[r1][c2] - map[r2][c1] - map[r2][c2]
                                + (r2-r1-1)*(c2-c1-1);
                    answer = std::max(answer, curr);
                }
            }
        }
    }
    std::cout << answer;

    return 0;
}