#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    while (q--) {
        int kind;
        std::cin >> kind;
        if (kind == 0) {
            int i, j, k;
            std::cin >> i >> j >> k;
            matrix[i][j] = k;
        } else {
            int i, j;
            std::cin >> i >> j;
            matrix[i].swap(matrix[j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}