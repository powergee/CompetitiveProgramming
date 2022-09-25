#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using Vector2D = std::vector<std::vector<int>>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m, k;
    std::cin >> n >> m >> k;
    
    Vector2D map(n+1, std::vector(m+1, 0));
    for (int i = 1; i <= n; ++i) {
        std::string line;
        std::cin >> line;
        for (int j = 1; j <= m; ++j) {
            map[i][j] = line[j-1] == 'B' ? 1 : 0;
        }
    }

    auto getAccVector = [&](int base) -> Vector2D {
        Vector2D result(n+1, std::vector(m+1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int correct = (base+(i-1)+(j-1)) % 2;
                int cell = (correct == map[i][j] ? 0 : 1);
                result[i][j] = result[i-1][j] + result[i][j-1] - result[i-1][j-1] + cell;
            }
        }
        return result;
    };

    auto bSum = getAccVector(1);
    auto wSum = getAccVector(0);

    int answer = INT32_MAX;
    for (int i = k; i <= n; ++i) {
        for (int j = k; j <= m; ++j) {
            int curr = std::min(
                bSum[i][j] - bSum[i-k][j] - bSum[i][j-k] + bSum[i-k][j-k],
                wSum[i][j] - wSum[i-k][j] - wSum[i][j-k] + wSum[i-k][j-k]
            );
            answer = std::min(answer, curr);
        }
    }

    std::cout << answer;

    return 0;
}